
/* --------------------------------------------------------------------  */
/*                                                                       */
/*                         Author: Jeff Earickson                        */
/*                      Colby College, Waterville, ME                    */
/*                         jaearick@colby.edu                            */
/*                                                                       */
/*This code may be distributed freely, provided this notice is retained. */
/*                                                                       */
/* --------------------------------------------------------------------  */

/*
 * pwck_search - 
 * quickly search a sorted list of words for the password in question.  
 * This replaces the system call to grep() used in the previous version 
 * of npasswd.  It is more secure (no system call) and much faster than 
 * using grep anyway.  *But* your dictionary must be in sorted order for 
 * this to work, ie:  
 *    cat wordlist.* | wordfilter | sort | uniq > dictionary
 * The "wordfilter" program is found in the npasswd directory.  It filters
 * out non-alphanumeric garbage from words (accents and junk from ISO
 * character sets), removes words that are shorter than the minimum
 * password length, and converts everything to lowercase.
 */

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "checkpasswd.h"

#define WORDBLOCK 2048   /* block size to read from dict (UNIX block) */
#define PASSWORDSIZE 9   /* max password length */

int pwck_search(which_dictionary, password)
char *which_dictionary,        /* pathname of dictionary */
     *password;                /* cleartext of password */
{
    char buf[WORDBLOCK];
    char first_letter, first_letter_in_block();
    int fd;
    size_t nread, n, npos, last;
    off_t dictsize, offset, getdictsize(), initial_seek();

    /* if open of dictionary fails, move on */
    /* otherwise get dictionary size and initial offset */
    if((fd = open(which_dictionary, O_RDONLY)) < 0) return(PWCK_OK);
    if((dictsize = getdictsize(fd)) < 0) return(PWCK_FAIL);
    offset = initial_seek(dictsize,password[0]);

#ifdef DEBUG
    printf("searching for %s in dictionary %s, size %d\n",
            password,which_dictionary,dictsize);
    printf("initial seek distance = %d bytes\n",offset);
#endif

    /* if the offset is zero, then we are searching for a */
    /* word at the beginning of the dictionary, so go ahead */
    /* and do the word-by-word search below */
    if(offset > 0)
    {
        /* otherwise get positioned in the dictionary */
        /* to buffer block that has our first letter  */
        do 
        {
            if(do_lseek(fd,offset) < 0) return(PWCK_FAIL);
            if((nread = getablock(fd,buf,sizeof(buf))) < 0) return(PWCK_FAIL);
            first_letter = first_letter_in_block(buf,nread);
            n = tolower(password[0]) - first_letter;
            if(n < 0) offset -= WORDBLOCK;
            if(n > 0) offset += WORDBLOCK;
            /* sanity check */
            if(offset < 0 || offset > dictsize)
            {
                fprintf(stderr,"bogus dictionary offset = %ld!!!,\n",offset);
                return(PWCK_FAIL);
            }
        }
        while(n != 0);

        /* back up one block so that we start in the first */
        /* block containing words with our first letter */
        offset -= WORDBLOCK;
    }
#ifdef DEBUG
    printf("offset before word search = %ld\n",offset);
#endif
    return(word_search(fd, offset, password));
}

int word_search(fd, offset, password)
/* returns PWCK_INDICT if password found in dictionary, PWCK_OK otherwise */
int   fd;         /* file descriptor of dictionary */
off_t offset;     /* byte offset into dictionary */
char  *password;  /* cleartext password */
{
    char *word, *getaword();
    char buf[WORDBLOCK];
    char pwtemp[PASSWORDSIZE];
    int  n, nread, nnext, wordtype;

    /* force first letter of password to lowercase the */
    /* dictionary is all lowercase words; we want to   */
    /* find passwords where only the initial letter is */
    /* capitalized, if in dictionary */
    (void) strcpy(pwtemp,password);
    pwtemp[0] = tolower(pwtemp[0]);

    for(;;)
    {
        /* get to the right spot in dictionary */
        if(do_lseek(fd,offset) < 0) return(PWCK_FAIL);
        if((nread = getablock(fd,buf,sizeof(buf))) < 0) return(PWCK_FAIL);
    
        /* get the first word in the block */
        /* may just be a partial word...   */
        wordtype = -1;
        word = getaword(buf,nread,&wordtype);
#ifdef DEBUG
/*
        printf("word_search: offset = %d, pw = %s, first word = %s\n",
                offset,pwtemp,word);
*/
#endif

        /* skip comparison if first word in */
        /* block is really only a partial word */
        if(word[0] == pwtemp[0])
        {
            if(strncmp(word,pwtemp,(size_t) PASSWORDSIZE) == 0) 
                return(PWCK_INDICT);
        }
    
        wordtype = 0;
        while((word = getaword(buf,nread,&wordtype)) != NULL)
        {
#ifdef DEBUG
/*
            printf("word_search: offset = %d, pw = %s, word = %s\n",
                    offset,pwtemp,word);
*/
#endif
            /* if the first letter of word is greater than */
            /* password letter, then password was not found */
            if(word[0] > pwtemp[0]) return(PWCK_OK);

            /* partial word at end of block, advance lseek */
            /* offset pointer to beginning of that word and */
            /* go get another block */
            if(wordtype > 0)
            {
                offset += wordtype; 
                break;
            }

            /* otherwise check word against password */
            if(strncmp(word,pwtemp,(size_t) PASSWORDSIZE) == 0) 
                return(PWCK_INDICT);
        }
    }
    /* we should never get to here */
    return(PWCK_FAIL);
}

off_t getdictsize(fd)
/* return the size of the dictionary file in bytes */
int fd;    /* file descriptor from open() */
{
    struct stat buf;

    if(fstat(fd,&buf) < 0)
    {
        perror("getdictsize: fstat");
        return(-1);
    }
    return(buf.st_size);
}

off_t initial_seek(dictsize, first_letter)
/* distance to seek into dictionary, based on */
/* first letter of word to be searched for */
off_t dictsize;    /* size of dictionary in bytes */
int first_letter;  /* first letter of the password */
{
    float perc;
    off_t dist;

    /* if first letter not alphabetic, */
    /* point to beginning of dictionary */
    if(!isalpha(first_letter)) return((off_t) 0);

    /* figure up linear percentage of seek distance */
    /* based on a sorted dictionary of 26 letters   */
    perc = ((float)(tolower(first_letter) - 'a'))/26.0;;
    dist = perc * dictsize;

    /* make sure dist is still in range 0 .. dictsize */
    if(dist < (off_t) 0) return((off_t) 0);
    if(dist > dictsize) return(dictsize);
    return(dist);
}

int do_lseek(fd, offset)
/* lseek into dictionary file offset bytes */
int fd;       /* file descriptor of dictionary */
off_t offset; /* seek distance from beginning of file */
{
    if(lseek(fd,offset,SEEK_SET) < 0)
    {
        fprintf(stderr,"bogus lseek offset = %d\n",offset);
        perror("lseek");
        return(-1);
    }
    return(0);
}

int getablock(fd, buf, bufsize)
/* binary read of dictionary file */
int fd;         /* file descriptor of dictionary */
char *buf;      /* buffer to read dictionary into */
size_t bufsize; /* size of buffer block, bytes */
{
    int nread;

    if((nread = read(fd,buf,bufsize)) < 0) perror("read");
    return(nread);
}

char first_letter_in_block(buf, nread)
/* skips over any partial word at the beginning of */
/* the buffer, and returns the first character of the */
/* first full word in the buffer */
char *buf;   /* buffer containing dictionary words */
int  nread;  /* number of useful bytes in buffer */
{
    int n;

    for(n = 0; n < nread; n++) if(buf[n] == '\n') return(buf[n+1]);
}

char *getaword(buf, maxchar, wordtype)
/* version of strtok that leaves buf contents alone */
char *buf;      /* buffer containing dictionary words */
int  maxchar;   /* number of characters in the buffer */
int  *wordtype; /* if wordtype < 0, then reset the pointer to zero */
                /* returns 0 for full word found, or np if partial word */
{
    static char word[WORDBLOCK];
    static int np;  /* points to the current spot in buf */
    int n, i;

    /* reset the static pointer if necessary   */
    np = (*wordtype == 0) ? np : 0;
    if(np > maxchar) return(NULL);

    /* look for the next newline relative to */
    /* the current buf pointer location */
    for(i = 0, n = np; n < maxchar; n++)
    {
        if(buf[n] == '\n') break;
        i++;               /* counts how many chars in word */
    }

    /* partial word, advance lseek offset */
    if(n >= maxchar) *wordtype = np;

    /* copy the next word out of buf */
    for(n = 0; n < i; n++) word[n] = buf[np+n];
    word[n] = '\0';

    /* advance the static pointer to start */
    /* next word (i chars + newline) */
    np += i+1;

    return(word);
}
