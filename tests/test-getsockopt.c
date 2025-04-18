/* Test getsockopt() function.
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

#include <config.h>

#include <sys/socket.h>

#include "signature.h"
#if !defined __sun
SIGNATURE_CHECK (getsockopt, int, (int, int, int, void *, socklen_t *));
#endif

#include <errno.h>
#include <unistd.h>

#include "sockets.h"
#include "macros.h"

int
main (void)
{
  (void) gl_sockets_startup (SOCKETS_1_1);

  /* Test behaviour for invalid file descriptors.  */
  {
    int value;
    socklen_t value_len = sizeof (value);

    errno = 0;
    ASSERT (getsockopt (-1, SOL_SOCKET, SO_REUSEADDR, &value, &value_len)
            == -1);
    ASSERT (errno == EBADF);
  }
  {
    int value;
    socklen_t value_len = sizeof (value);

    close (99);
    errno = 0;
    ASSERT (getsockopt (99, SOL_SOCKET, SO_REUSEADDR, &value, &value_len)
            == -1);
    ASSERT (errno == EBADF);
  }

  return test_exit_status;
}
