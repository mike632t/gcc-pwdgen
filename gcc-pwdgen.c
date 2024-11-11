/*
 * gcc-pwdgen.c
 *
 * A  random password generator to generate passwords made up from triplets 
 * comprising of a constant, a vowel, and a constant.
 *
 * 'cc pwdgen'
 * 'link pwdgen,sys$library:vaxcrtl.olb/lib'
 *
 * This  program is free software: you can redistribute it and/or modify it
 * under  the terms of the GNU General Public License as published  by  the
 * Free  Software Foundation, either version 3 of the License, or (at  your
 * option) any later version.
 *
 * This  program  is distributed in the hope that it will  be  useful,  but
 * WITHOUT   ANY   WARRANTY;   without even   the   implied   warranty   of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You  should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 23 Feb 16   0.1   - Initial version - MT 
 * 16 Mar 16   0.2   - Added some numbers into the character strings - MT 
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORDS 5 /* How many passwords to generate. */
#define LENGTH 11   /* Length of the password. */
#define SIZE 3      /* Size of letter group, use an odd number greater than 1. */


char consonant[] = "bcdfghjk1mnpqr5tvwz"; /* Note - X,Y and zero all left */
char vowel[] = "a4e3iou";                 /* out intentionally. */
char digit[] = "123456789";

int main(int argc, char *argv[]) {
  int  loop; /* Counts passwords generated. */
  int  i,j; /* Counters for characters in each password. */
  char passwd[LENGTH + 1]; /* Character array to hold password 'string'. */

  /* Seed random number generator with an unsigned value. */
  srand((unsigned)(time(NULL)));

  for (loop = 0; loop < PASSWORDS; loop++) {

    /* Generate letter groups. */
    for (i = 0; i < (LENGTH / SIZE); i++) {
      for (j = 0; j < SIZE; j++){
        if ((j % 2) == 0)
          passwd[i * SIZE +j] = consonant[rand() % strlen(consonant)];
        else
          passwd[i * SIZE +j] = vowel[rand() % strlen(vowel)];
      }
    }

    /* Pad out password with digits if required. */
    i *= SIZE;
    while (i < LENGTH) {
      passwd[i] = digit[rand() % strlen(digit)];
      i++;
    }

    /* Terminate password 'string' with a null character. */
    passwd[LENGTH] = '\0';

    /* Print password (with dashes between groups). */
    for (i = 0; i < LENGTH; i++) {
      if (((i % SIZE) == 0) && (i >0)) printf("%c",'-');
      printf ("%c",passwd[i]);
    }
    printf("\n");
  }
} 
