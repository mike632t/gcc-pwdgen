/*
 * gcc-pwdgen.c
 * 
 * Copyright (C) 2012  MT
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
 * 17 Sep 23   0.3   - Updated variable names - MT
 *                   - Valid characters defined as two sets of constants to
 *                     allow more complex passwords with special characters
 *                     and  both upper and lower case letters to be created
 *                     if needed - MT
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORDS 5 /* How many passwords to generate. */
#define LENGTH 11   /* Length of the password. */
#define SIZE 3      /* Size of letter group, use an odd number greater than 1. */

#if defined(COMPLEX)
#define CONSONANTS "bcdfghklmnpqrstvwyBCDFGKLMNPQRSTVWY"
#define VOWELS "a4e3io0uA4E3I1O0U"
#define DIGITS "123456789"
#define SPECIAL "!\"#$%&'()*+.:;<>?@[/]^_{|}" 
#else
#define CONSONANTS "bcdfghklmnpqrstvwy"
#define VOWELS "aeiou"
#define DIGITS "123456789"
#define SPECIAL ""  /* No special characters as they are not always allowed */
#endif

char* concat(const char* first, const char* second) /* Concatenate strings */
{
   char* result = malloc(strlen(first) + strlen(second) + 1);
   sprintf(result, "%s%s", first, second);
   return result;
}

int main()
{
   char* s_consonant = CONSONANTS;
   char* s_vowel = VOWELS;
   char* s_digit = concat(DIGITS, SPECIAL); /* Explicitly concatenate strings for portability */

   int i_count; /* Counts passwords generated. */
   int i_i, i_j; /* Counters for characters in each password. */
   char s_passwd[LENGTH + 1]; /* Character array to hold password 'string'. */

   srand((unsigned)(time(NULL))); /* Seed random number generator with an unsigned value. */

   for (i_count = 0; i_count < PASSWORDS; i_count++)
   {
      for (i_i = 0; i_i < (LENGTH / SIZE); i_i++) /* Generate letter groups. */
      { 
         for (i_j = 0; i_j < SIZE; i_j++){
         if ((i_j % 2) == 0)
            s_passwd[i_i * SIZE +i_j] = s_consonant[rand() % strlen(s_consonant)];
         else
            s_passwd[i_i * SIZE +i_j] = s_vowel[rand() % strlen(s_vowel)];
         }
      }

      i_i *= SIZE;
      while (i_i < LENGTH) /* Pad out password with digits if required. */
      { 
         s_passwd[i_i] = s_digit[rand() % strlen(s_digit)];
         i_i++;
      }

      s_passwd[LENGTH] = '\0'; /* Terminate password 'string' with a null character. */

      for (i_i = 0; i_i < LENGTH; i_i++) /* Print password in groups of three letters. */
      { 
         if (((i_i % SIZE) == 0) && (i_i >0)) printf("%c",'-'); 
         printf ("%c",s_passwd[i_i]);
      }
      printf("\n");
   }
   exit(0);
}
