/* Test for NaN that does not need libm.
   Copyright (C) 2007-2025 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* This file uses HAVE_ISNAND_IN_LIBC.  */
#if !_GL_CONFIG_H_INCLUDED
 #error "Please include config.h first."
#endif

#if HAVE_ISNAND_IN_LIBC
/* Get declaration of isnan macro.  */
# include <math.h>
# if (__GNUC__ >= 4) || (__clang_major__ >= 4)
   /* GCC >= 4.0 and clang provide a type-generic built-in for isnan.  */
#  undef isnand
#  define isnand(x) __builtin_isnan ((double)(x))
# else
#  undef isnand
#  define isnand(x) isnan ((double)(x))
# endif
#else
/* Test whether X is a NaN.  */
# undef isnand
# define isnand rpl_isnand
extern
# ifdef __cplusplus
"C"
# endif
int isnand (double x);
#endif

/* Tell <math.h> that our isnand does not need libm.  */
#define HAVE_ISNAND_NOLIBM 1
