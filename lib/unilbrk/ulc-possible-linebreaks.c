/* Line breaking of strings.
   Copyright (C) 2001-2003, 2006-2025 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2001.

   This file is free software.
   It is dual-licensed under "the GNU LGPLv3+ or the GNU GPLv2+".
   You can redistribute it and/or modify it under either
     - the terms of the GNU Lesser General Public License as published
       by the Free Software Foundation, either version 3, or (at your
       option) any later version, or
     - the terms of the GNU General Public License as published by the
       Free Software Foundation; either version 2, or (at your option)
       any later version, or
     - the same dual license "the GNU LGPLv3+ or the GNU GPLv2+".

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License and the GNU General Public License
   for more details.

   You should have received a copy of the GNU Lesser General Public
   License and of the GNU General Public License along with this
   program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <config.h>

/* Specification.  */
#include "unilbrk.h"

#include <stdlib.h>
#include <string.h>

#include "c-ctype.h"
#include "uniconv.h"
#include "unilbrk/internal.h"
#include "unilbrk/lbrktables.h"
#include "unilbrk/ulc-common.h"

/* Line breaking of a string in an arbitrary encoding.

   We convert the input string to Unicode.

   The standardized Unicode encodings are UTF-8, UCS-2, UCS-4, UTF-16,
   UTF-16BE, UTF-16LE, UTF-7.  UCS-2 supports only characters up to
   \U0000FFFF.  UTF-16 and variants support only characters up to
   \U0010FFFF.  UTF-7 is way too complex and not supported by glibc-2.1.
   UCS-4 specification leaves doubts about endianness and byte order mark.
   glibc currently interprets it as big endian without byte order mark,
   but this is not backed by an RFC.  So we use UTF-8. It supports
   characters up to \U7FFFFFFF and is unambiguously defined.  */

static void
ulc_possible_linebreaks_internal (const char *s, size_t n, const char *encoding,
                                  int cr, char *p)
{
  if (n > 0)
    {
      if (is_utf8_encoding (encoding))
        u8_possible_linebreaks_loop ((const uint8_t *) s, n, encoding, cr, p);
      else
        {
          /* Convert the string to UTF-8 and build a translation table
             from offsets into s to offsets into the translated string.  */
          size_t *offsets = (size_t *) malloc (n * sizeof (size_t));

          if (offsets != NULL)
            {
              uint8_t *t;
              size_t m;

              t = u8_conv_from_encoding (encoding, iconveh_question_mark,
                                         s, n, offsets, NULL, &m);
              if (t != NULL)
                {
                  char *q = (char *) (m > 0 ? malloc (m) : NULL);

                  if (m == 0 || q != NULL)
                    {
                      size_t i;

                      /* Determine the possible line breaks of the UTF-8
                         string.  */
                      u8_possible_linebreaks_loop (t, m, encoding, cr, q);

                      /* Translate the result back to the original string.  */
                      memset (p, UC_BREAK_PROHIBITED, n);
                      for (i = 0; i < n; i++)
                        if (offsets[i] != (size_t)(-1))
                          p[i] = q[offsets[i]];

                      free (q);
                      free (t);
                      free (offsets);
                      return;
                    }
                  free (t);
                }
              free (offsets);
            }

          /* Impossible to convert.  */
#if C_CTYPE_ASCII
          if (is_all_ascii (s, n))
            {
              /* ASCII is a subset of UTF-8.  */
              u8_possible_linebreaks_loop ((const uint8_t *) s, n, encoding, cr, p);
              return;
            }
#endif
          /* We have a non-ASCII string and cannot convert it.
             Don't produce line breaks except those already present in the
             input string.  All we assume here is that the encoding is
             minimally ASCII compatible.  */
          {
            const char *s_end = s + n;
            while (s < s_end)
              {
                *p = (*s == '\n'
                      ? UC_BREAK_MANDATORY
                      : ((cr >= 0
                          && *s == '\r'
                          && s + 1 < s_end
                          && *(s + 1) == '\n')
                         ? UC_BREAK_CR_BEFORE_LF
                         : UC_BREAK_PROHIBITED));
                s++;
                p++;
              }
          }
        }
    }
}

#if defined IN_LIBUNISTRING
/* For backward compatibility with older versions of libunistring.  */

# undef ulc_possible_linebreaks

void
ulc_possible_linebreaks (const char *s, size_t n, const char *encoding,
                         char *p)
{
  ulc_possible_linebreaks_internal (s, n, encoding, -1, p);
}

#endif

void
ulc_possible_linebreaks_v2 (const char *s, size_t n, const char *encoding,
                            char *p)
{
  ulc_possible_linebreaks_internal (s, n, encoding, LBP_CR, p);
}


#ifdef TEST

#include <stdio.h>
#include <locale.h>
#include <string.h>

/* Read the contents of an input stream, and return it, terminated with a NUL
   byte. */
char *
read_file (FILE *stream)
{
#define BUFSIZE 4096
  char *buf = NULL;
  int alloc = 0;
  int size = 0;
  int count;

  while (! feof (stream))
    {
      if (size + BUFSIZE > alloc)
        {
          alloc = alloc + alloc / 2;
          if (alloc < size + BUFSIZE)
            alloc = size + BUFSIZE;
          buf = realloc (buf, alloc);
          if (buf == NULL)
            {
              fprintf (stderr, "out of memory\n");
              exit (1);
            }
        }
      count = fread (buf + size, 1, BUFSIZE, stream);
      if (count == 0)
        {
          if (ferror (stream))
            {
              perror ("fread");
              exit (1);
            }
        }
      else
        size += count;
    }
  buf = realloc (buf, size + 1);
  if (buf == NULL)
    {
      fprintf (stderr, "out of memory\n");
      exit (1);
    }
  buf[size] = '\0';
  return buf;
#undef BUFSIZE
}

int
main (int argc, char * argv[])
{
  setlocale (LC_CTYPE, "");
  if (argc == 1)
    {
      /* Display all the break opportunities in the input string.  */
      char *input = read_file (stdin);
      int length = strlen (input);
      char *breaks = malloc (length);
      int i;

      ulc_possible_linebreaks_v2 (input, length, locale_charset (), breaks);

      for (i = 0; i < length; i++)
        {
          switch (breaks[i])
            {
            case UC_BREAK_POSSIBLE:
              putc ('|', stdout);
              break;
            case UC_BREAK_MANDATORY:
              break;
            case UC_BREAK_CR_BEFORE_LF:
              break;
            case UC_BREAK_PROHIBITED:
              break;
            default:
              abort ();
            }
          putc (input[i], stdout);
        }

      free (breaks);

      return 0;
    }
  else
    return 1;
}

#endif /* TEST */
