/* Test of conversion of multibyte character to 16-bit wide characters.
   Copyright (C) 2008-2025 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <config.h>

#include <uchar.h>

#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "localcharset.h"
#include "macros.h"

#if defined _WIN32 && !defined __CYGWIN__

static int
test_one_locale (const char *name, int codepage)
{
  mbstate_t state;
  char16_t wc;
  size_t ret;

# if 1
  /* Portable code to set the locale.  */
  {
    char name_with_codepage[1024];

    sprintf (name_with_codepage, "%s.%d", name, codepage);

    /* Set the locale.  */
    if (setlocale (LC_ALL, name_with_codepage) == NULL)
      return 77;
  }
# else
  /* Hacky way to set a locale.codepage combination that setlocale() refuses
     to set.  */
  {
    /* Codepage of the current locale, set with setlocale().
       Not necessarily the same as GetACP().  */
    extern __declspec(dllimport) unsigned int __lc_codepage;

    /* Set the locale.  */
    if (setlocale (LC_ALL, name) == NULL)
      return 77;

    /* Clobber the codepage and MB_CUR_MAX, both set by setlocale().  */
    __lc_codepage = codepage;
    switch (codepage)
      {
      case 1252:
      case 1256:
        MB_CUR_MAX = 1;
        break;
      case 932:
      case 950:
      case 936:
        MB_CUR_MAX = 2;
        break;
      case 54936:
      case 65001:
        MB_CUR_MAX = 4;
        break;
      }

    /* Test whether the codepage is really available.  */
    memset (&state, '\0', sizeof (mbstate_t));
    if (mbrtoc16 (&wc, " ", 1, &state) == (size_t)(-1))
      return 77;
  }
# endif

  /* Test zero-length input.  */
  {
    memset (&state, '\0', sizeof (mbstate_t));
    wc = (char16_t) 0xBADF;
    ret = mbrtoc16 (&wc, "x", 0, &state);
    ASSERT (ret == (size_t)(-2));
    ASSERT (mbsinit (&state));
  }

  /* Test NUL byte input.  */
  {
    memset (&state, '\0', sizeof (mbstate_t));
    wc = (char16_t) 0xBADF;
    ret = mbrtoc16 (&wc, "", 1, &state);
    ASSERT (ret == 0);
    ASSERT (wc == 0);
    ASSERT (mbsinit (&state));
    ret = mbrtoc16 (NULL, "", 1, &state);
    ASSERT (ret == 0);
    ASSERT (mbsinit (&state));
  }

  /* Test single-byte input.  */
  {
    int c;
    char buf[1];

    memset (&state, '\0', sizeof (mbstate_t));
    for (c = 0; c < 0x100; c++)
      switch (c)
        {
        case '\t': case '\v': case '\f':
        case ' ': case '!': case '"': case '#': case '%':
        case '&': case '\'': case '(': case ')': case '*':
        case '+': case ',': case '-': case '.': case '/':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case ':': case ';': case '<': case '=': case '>':
        case '?':
        case 'A': case 'B': case 'C': case 'D': case 'E':
        case 'F': case 'G': case 'H': case 'I': case 'J':
        case 'K': case 'L': case 'M': case 'N': case 'O':
        case 'P': case 'Q': case 'R': case 'S': case 'T':
        case 'U': case 'V': case 'W': case 'X': case 'Y':
        case 'Z':
        case '[': case '\\': case ']': case '^': case '_':
        case 'a': case 'b': case 'c': case 'd': case 'e':
        case 'f': case 'g': case 'h': case 'i': case 'j':
        case 'k': case 'l': case 'm': case 'n': case 'o':
        case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y':
        case 'z': case '{': case '|': case '}': case '~':
          /* c is in the ISO C "basic character set".  */
          buf[0] = c;
          wc = (char16_t) 0xBADF;
          ret = mbrtoc16 (&wc, buf, 1, &state);
          ASSERT (ret == 1);
          ASSERT (wc == c);
          ASSERT (mbsinit (&state));
          ret = mbrtoc16 (NULL, buf, 1, &state);
          ASSERT (ret == 1);
          ASSERT (mbsinit (&state));
          break;
        }
  }

  /* Test special calling convention, passing a NULL pointer.  */
  {
    memset (&state, '\0', sizeof (mbstate_t));
    wc = (char16_t) 0xBADF;
    ret = mbrtoc16 (&wc, NULL, 5, &state);
    ASSERT (ret == 0);
    ASSERT (wc == (char16_t) 0xBADF);
    ASSERT (mbsinit (&state));
  }

  switch (codepage)
    {
    case 1252:
      /* Locale encoding is CP1252, an extension of ISO-8859-1.  */
      {
        char input[] = "B\374\337er"; /* "Büßer" */
        memset (&state, '\0', sizeof (mbstate_t));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == 'B');
        ASSERT (mbsinit (&state));
        input[0] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 1, 1, &state);
        ASSERT (ret == 1);
        ASSERT (c32tob (wc) == (unsigned char) '\374');
        ASSERT (wc == 0x00FC);
        ASSERT (mbsinit (&state));
        input[1] = '\0';

        /* Test support of NULL first argument.  */
        ret = mbrtoc16 (NULL, input + 2, 3, &state);
        ASSERT (ret == 1);
        ASSERT (mbsinit (&state));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 2, 3, &state);
        ASSERT (ret == 1);
        ASSERT (c32tob (wc) == (unsigned char) '\337');
        ASSERT (wc == 0x00DF);
        ASSERT (mbsinit (&state));
        input[2] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 3, 2, &state);
        ASSERT (ret == 1);
        ASSERT (wc == 'e');
        ASSERT (mbsinit (&state));
        input[3] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 4, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == 'r');
        ASSERT (mbsinit (&state));
      }
      return 0;

    case 1256:
      /* Locale encoding is CP1256, not the same as ISO-8859-6.  */
      {
        char input[] = "x\302\341\346y"; /* "xآلوy" */
        memset (&state, '\0', sizeof (mbstate_t));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == 'x');
        ASSERT (mbsinit (&state));
        input[0] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 1, 1, &state);
        ASSERT (ret == 1);
        ASSERT (c32tob (wc) == (unsigned char) '\302');
        ASSERT (wc == 0x0622);
        ASSERT (mbsinit (&state));
        input[1] = '\0';

        /* Test support of NULL first argument.  */
        ret = mbrtoc16 (NULL, input + 2, 3, &state);
        ASSERT (ret == 1);
        ASSERT (mbsinit (&state));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 2, 3, &state);
        ASSERT (ret == 1);
        ASSERT (c32tob (wc) == (unsigned char) '\341');
        ASSERT (wc == 0x0644);
        ASSERT (mbsinit (&state));
        input[2] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 3, 2, &state);
        ASSERT (ret == 1);
        ASSERT (c32tob (wc) == (unsigned char) '\346');
        ASSERT (wc == 0x0648);
        ASSERT (mbsinit (&state));
        input[3] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 4, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == 'y');
        ASSERT (mbsinit (&state));
      }
      return 0;

    case 65001:
      /* Locale encoding is CP65001 = UTF-8.  */
      if (strcmp (locale_charset (), "UTF-8") != 0)
        return 77;
      {
        char input[] = "s\303\274\303\237\360\237\230\213!"; /* "süß😋!" */
        memset (&state, '\0', sizeof (mbstate_t));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == 's');
        ASSERT (mbsinit (&state));
        input[0] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 1, 1, &state);
        ASSERT (ret == (size_t)(-2));
        ASSERT (wc == (char16_t) 0xBADF);
        #if 0
        ASSERT (!mbsinit (&state));
        #endif
        input[1] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 2, 7, &state);
        ASSERT (ret == 1);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x00FC);
        ASSERT (mbsinit (&state));
        input[2] = '\0';

        /* Test support of NULL first argument.  */
        ret = mbrtoc16 (NULL, input + 3, 6, &state);
        ASSERT (ret == 2);
        ASSERT (mbsinit (&state));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 3, 6, &state);
        ASSERT (ret == 2);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x00DF);
        ASSERT (mbsinit (&state));
        input[3] = '\0';
        input[4] = '\0';

        /* Test support of NULL first argument.  */
        ret = mbrtoc16 (NULL, input + 5, 4, &state);
        ASSERT (ret == 4);
        ret = mbrtoc16 (NULL, input + 9, 0, &state);
        ASSERT (ret == (size_t)(-3));
        ASSERT (mbsinit (&state));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 5, 4, &state);
        ASSERT (ret == 4);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0xD83D); /* expect UTF-16 encoding */
        input[5] = '\0';
        input[6] = '\0';
        input[7] = '\0';
        input[8] = '\0';
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 9, 0, &state);
        ASSERT (ret == (size_t)(-3));
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0xDE0B); /* expect UTF-16 encoding */
        ASSERT (mbsinit (&state));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 9, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == '!');
        ASSERT (mbsinit (&state));

        /* Test some invalid input.  */
        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\377", 1, &state); /* 0xFF */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\303\300", 2, &state); /* 0xC3 0xC0 */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\343\300", 2, &state); /* 0xE3 0xC0 */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\343\300\200", 3, &state); /* 0xE3 0xC0 0x80 */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\343\200\300", 3, &state); /* 0xE3 0x80 0xC0 */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\363\300", 2, &state); /* 0xF3 0xC0 */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\363\300\200\200", 4, &state); /* 0xF3 0xC0 0x80 0x80 */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\363\200\300", 3, &state); /* 0xF3 0x80 0xC0 */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\363\200\300\200", 4, &state); /* 0xF3 0x80 0xC0 0x80 */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\363\200\200\300", 4, &state); /* 0xF3 0x80 0x80 0xC0 */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);
      }
      return 0;

    case 932:
      /* Locale encoding is CP932, similar to Shift_JIS.  */
      {
        char input[] = "<\223\372\226\173\214\352>"; /* "<日本語>" */
        memset (&state, '\0', sizeof (mbstate_t));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == '<');
        ASSERT (mbsinit (&state));
        input[0] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 1, 2, &state);
        ASSERT (ret == 2);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x65E5);
        ASSERT (mbsinit (&state));
        input[1] = '\0';
        input[2] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 3, 1, &state);
        ASSERT (ret == (size_t)(-2));
        ASSERT (wc == (char16_t) 0xBADF);
        #if 0
        ASSERT (!mbsinit (&state));
        #endif
        input[3] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 4, 4, &state);
        ASSERT (ret == 1);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x672C);
        ASSERT (mbsinit (&state));
        input[4] = '\0';

        /* Test support of NULL first argument.  */
        ret = mbrtoc16 (NULL, input + 5, 3, &state);
        ASSERT (ret == 2);
        ASSERT (mbsinit (&state));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 5, 3, &state);
        ASSERT (ret == 2);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x8A9E);
        ASSERT (mbsinit (&state));
        input[5] = '\0';
        input[6] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 7, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == '>');
        ASSERT (mbsinit (&state));

        /* Test some invalid input.  */
        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\377", 1, &state); /* 0xFF */
        ASSERT ((ret == (size_t)-1 && errno == EILSEQ) || ret == (size_t)-2);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\225\377", 2, &state); /* 0x95 0xFF */
        ASSERT ((ret == (size_t)-1 && errno == EILSEQ) || (ret == 2 && wc == 0x30FB));
      }
      return 0;

    case 950:
      /* Locale encoding is CP950, similar to Big5.  */
      {
        char input[] = "<\244\351\245\273\273\171>"; /* "<日本語>" */
        memset (&state, '\0', sizeof (mbstate_t));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == '<');
        ASSERT (mbsinit (&state));
        input[0] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 1, 2, &state);
        ASSERT (ret == 2);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x65E5);
        ASSERT (mbsinit (&state));
        input[1] = '\0';
        input[2] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 3, 1, &state);
        ASSERT (ret == (size_t)(-2));
        ASSERT (wc == (char16_t) 0xBADF);
        #if 0
        ASSERT (!mbsinit (&state));
        #endif
        input[3] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 4, 4, &state);
        ASSERT (ret == 1);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x672C);
        ASSERT (mbsinit (&state));
        input[4] = '\0';

        /* Test support of NULL first argument.  */
        ret = mbrtoc16 (NULL, input + 5, 3, &state);
        ASSERT (ret == 2);
        ASSERT (mbsinit (&state));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 5, 3, &state);
        ASSERT (ret == 2);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x8A9E);
        ASSERT (mbsinit (&state));
        input[5] = '\0';
        input[6] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 7, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == '>');
        ASSERT (mbsinit (&state));

        /* Test some invalid input.  */
        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\377", 1, &state); /* 0xFF */
        ASSERT ((ret == (size_t)-1 && errno == EILSEQ) || ret == (size_t)-2);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\225\377", 2, &state); /* 0x95 0xFF */
        ASSERT ((ret == (size_t)-1 && errno == EILSEQ) || (ret == 2 && wc == '?'));
      }
      return 0;

    case 936:
      /* Locale encoding is CP936 = GBK, an extension of GB2312.  */
      {
        char input[] = "<\310\325\261\276\325\132>"; /* "<日本語>" */
        memset (&state, '\0', sizeof (mbstate_t));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == '<');
        ASSERT (mbsinit (&state));
        input[0] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 1, 2, &state);
        ASSERT (ret == 2);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x65E5);
        ASSERT (mbsinit (&state));
        input[1] = '\0';
        input[2] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 3, 1, &state);
        ASSERT (ret == (size_t)(-2));
        ASSERT (wc == (char16_t) 0xBADF);
        #if 0
        ASSERT (!mbsinit (&state));
        #endif
        input[3] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 4, 4, &state);
        ASSERT (ret == 1);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x672C);
        ASSERT (mbsinit (&state));
        input[4] = '\0';

        /* Test support of NULL first argument.  */
        ret = mbrtoc16 (NULL, input + 5, 3, &state);
        ASSERT (ret == 2);
        ASSERT (mbsinit (&state));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 5, 3, &state);
        ASSERT (ret == 2);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x8A9E);
        ASSERT (mbsinit (&state));
        input[5] = '\0';
        input[6] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 7, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == '>');
        ASSERT (mbsinit (&state));

        /* Test some invalid input.  */
        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\377", 1, &state); /* 0xFF */
        ASSERT ((ret == (size_t)-1 && errno == EILSEQ) || ret == (size_t)-2);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\225\377", 2, &state); /* 0x95 0xFF */
        ASSERT ((ret == (size_t)-1 && errno == EILSEQ) || (ret == 2 && wc == '?'));
      }
      return 0;

    case 54936:
      /* Locale encoding is CP54936 = GB18030.  */
      if (strcmp (locale_charset (), "GB18030") != 0)
        return 77;
      {
        char input[] = "s\250\271\201\060\211\070\224\071\375\067!"; /* "süß😋!" */
        memset (&state, '\0', sizeof (mbstate_t));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == 's');
        ASSERT (mbsinit (&state));
        input[0] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 1, 1, &state);
        ASSERT (ret == (size_t)(-2));
        ASSERT (wc == (char16_t) 0xBADF);
        #if 0
        ASSERT (!mbsinit (&state));
        #endif
        input[1] = '\0';

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 2, 9, &state);
        ASSERT (ret == 1);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x00FC);
        ASSERT (mbsinit (&state));
        input[2] = '\0';

        /* Test support of NULL first argument.  */
        ret = mbrtoc16 (NULL, input + 3, 8, &state);
        ASSERT (ret == 4);
        ASSERT (mbsinit (&state));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 3, 8, &state);
        ASSERT (ret == 4);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0x00DF);
        ASSERT (mbsinit (&state));
        input[3] = '\0';
        input[4] = '\0';
        input[5] = '\0';
        input[6] = '\0';

        /* Test support of NULL first argument.  */
        ret = mbrtoc16 (NULL, input + 7, 4, &state);
        ASSERT (ret == 4);
        ret = mbrtoc16 (NULL, input + 11, 0, &state);
        ASSERT (ret == (size_t)(-3));
        ASSERT (mbsinit (&state));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 7, 4, &state);
        ASSERT (ret == 4);
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0xD83D); /* expect UTF-16 encoding */
        input[7] = '\0';
        input[8] = '\0';
        input[9] = '\0';
        input[10] = '\0';
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 11, 0, &state);
        ASSERT (ret == (size_t)(-3));
        ASSERT (c32tob (wc) == EOF);
        ASSERT (wc == 0xDE0B); /* expect UTF-16 encoding */
        ASSERT (mbsinit (&state));

        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, input + 11, 1, &state);
        ASSERT (ret == 1);
        ASSERT (wc == '!');
        ASSERT (mbsinit (&state));

        /* Test some invalid input.  */
        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\377", 1, &state); /* 0xFF */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\225\377", 2, &state); /* 0x95 0xFF */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\201\045", 2, &state); /* 0x81 0x25 */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\201\060\377", 3, &state); /* 0x81 0x30 0xFF */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\201\060\377\064", 4, &state); /* 0x81 0x30 0xFF 0x34 */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);

        memset (&state, '\0', sizeof (mbstate_t));
        wc = (char16_t) 0xBADF;
        ret = mbrtoc16 (&wc, "\201\060\211\072", 4, &state); /* 0x81 0x30 0x89 0x3A */
        ASSERT (ret == (size_t)-1);
        ASSERT (errno == EILSEQ);
      }
      return 0;

    default:
      return 1;
    }
}

int
main (int argc, char *argv[])
{
  int codepage = atoi (argv[argc - 1]);
  int result;
  int i;

  result = 77;
  for (i = 1; i < argc - 1; i++)
    {
      int ret = test_one_locale (argv[i], codepage);

      if (ret != 77)
        result = ret;
    }

  if (result == 77)
    {
      if (test_exit_status != EXIT_SUCCESS)
        return test_exit_status;
      fprintf (stderr, "Skipping test: found no locale with codepage %d\n",
               codepage);
    }
  return (result ? result : test_exit_status);
}

#else

int
main (int argc, char *argv[])
{
  fputs ("Skipping test: not a native Windows system\n", stderr);
  return 77;
}

#endif
