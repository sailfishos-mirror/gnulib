# fcntl-safer.m4
# serial 9
dnl Copyright (C) 2005-2007, 2009-2025 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

AC_DEFUN([gl_FCNTL_SAFER],
[
  dnl Prerequisites of lib/open-safer.c.
  AC_REQUIRE([gl_PROMOTED_TYPE_MODE_T])
])

AC_DEFUN([gl_OPENAT_SAFER],
[
  AC_REQUIRE([gl_FCNTL_SAFER])
])
