# config-h.m4
# serial 1
dnl Copyright (C) 2006, 2009-2025 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

# Say that -DHAVE_CONFIG_H is not needed.

dnl Written by Paul Eggert.

# This package's source files all include config.h unconditionally,
# so there's no need to pass -DHAVE_CONFIG_H to the compiler.
AC_DEFUN([gl_CONFIG_H],
  [AC_CONFIG_COMMANDS_PRE([test "X$DEFS" = X-DHAVE_CONFIG_H && DEFS=])])
