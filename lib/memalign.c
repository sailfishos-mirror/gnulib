/* Allocate memory with indefinite extent and specified alignment.
   Copyright (C) 2020-2021 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <config.h>

/* Specification.  */
#include <malloc.h>

#include <stdlib.h>

void *
memalign (size_t alignment, size_t size)
#undef memalign
{
  if (alignment < 4)
    /* The malloc() result has an alignment of at least 4 on all platforms.
       On platforms where memalign() exists, malloc() sets errno upon
      failure.  */
    return malloc (size);

  return memalign (alignment, size);
}
