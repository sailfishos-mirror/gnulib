/* Test of fmal().
   Copyright (C) 2011-2025 Free Software Foundation, Inc.

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

/* Written by Bruno Haible <bruno@clisp.org>, 2011.  */

#include <config.h>

#include <math.h>

#include "signature.h"
SIGNATURE_CHECK (fmal, long double, (long double, long double, long double));

#include "fpucw.h"
#include "isnanl-nolibm.h"
#include "infinity.h"
#include "nan.h"
#include "macros.h"

#undef INFINITY
#undef NAN

#define DOUBLE long double
#define ISNAN isnanl
#define INFINITY Infinityl ()
#define NAN NaNl ()
#define L_(literal) literal##L
#include "test-fma1.h"

int
main ()
{
  DECL_LONG_DOUBLE_ROUNDING

  BEGIN_LONG_DOUBLE_ROUNDING ();

  test_function (fmal);

  return test_exit_status;
}
