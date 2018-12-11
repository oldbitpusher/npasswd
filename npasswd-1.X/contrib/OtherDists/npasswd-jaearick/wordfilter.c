#include <stdio.h>
#include <strings.h>

#ifndef    CONFIG_FILE
#define    CONFIG_FILE    "/usr/adm/passwd.conf"
#endif

main()
/* wordfilter program for dictionary construction, to clean up */
/* a raw wordlist.  Words of length < min_length are ignored.  */
/* Spurious punctuation are removed from words, and max_length */
/* characters of the word are sent to stdout.  This program is */
/* meant to be used as a filter program, ie:                   */
/* "cat raw_wordlist | wordfilter | sort | uniq > dictionary"  */
{
    char word[40], tmp[40];
    char *configfile = CONFIG_FILE;      /* Configuration file */
    extern int min_length, max_length;
    int  i, j, length;

    /* go read the config file */
    /* to get min and max length */
    readconfig(configfile);

    /* read thru wordlist, writing out all that fits */
    while(scanf("%s",word) != EOF)
    {
	/* throw back fish under legal limit */
        length = strlen(word);
        if(length < min_length) continue;

        /* filter out non-alphanumeric letters */
        for(i=0, j=0; i < length; i++)
        {
            /* quit checking if the word is long enough */
            /* if(j >= max_length) break; */
            if(isalnum(word[i])) 
            {
                tmp[j] = tolower(word[i]);
                j++;
            }
        }
        tmp[j] = '\0';
        length = strlen(tmp);
        if(length >= min_length) printf("%s\n",tmp);
    }
}
