/*----------------------------------------------------------------------------*
|                                                                             |
|                           Author: Donald Olivier                            |
|                      Instructional Computing Facility                       |
|                      Harvard School of Public Health                        |
|                            677 Huntington Ave.                              |
|                             Boston, MA 02115                                |
|                           don@hsph.harvard.edu                              |
|                                                                             |
|    This code may be distributed freely, provided this notice is retained.   |
|                                                                             |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
| CFText.h								      |
*----------------------------------------------------------------------------*/

#ifndef _CFText
#define _CFText

/*----------------------------------------------------------------------------*
| An iterator returning CrackFilter items implied by strings in a text	      |
| (meant for gecos field and "dotfiles")				      |
*----------------------------------------------------------------------------*/

struct textIter {
    char* text;
    char* slimit;
    char* p;
};

char* CFText();                  /* char* CFText(char*); */
/*
void textFix();
char* textCombine();
void textPair();
*/

#endif /* ! _CFText */
