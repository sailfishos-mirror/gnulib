/* Test of log1pf() function.
   Copyright (C) 2012-2025 Free Software Foundation, Inc.

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

#include <math.h>

#include "isnanf-nolibm.h"
#include "minus-zero.h"
#include "infinity.h"
#include "nan.h"
#include "macros.h"

#undef INFINITY
#undef NAN

#define DOUBLE float
#define ISNAN isnanf
#define INFINITY Infinityf ()
#define NAN NaNf ()
#define L_(literal) literal##f
#define MINUS_ZERO minus_zerof
#define LOG1P log1pf
#include "test-log1p-ieee.h"

int
main ()
{
  test_function ();

  return test_exit_status;
}
