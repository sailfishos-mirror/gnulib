# asm-underscore.m4
# serial 6
dnl Copyright (C) 2010-2025 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

dnl From Bruno Haible. Based on as-underscore.m4 in GNU clisp.

# gl_ASM_SYMBOL_PREFIX
# Tests for the prefix of C symbols at the assembly language level and the
# linker level. This prefix is either an underscore or empty. Defines the
# C macro USER_LABEL_PREFIX to this prefix, and sets ASM_SYMBOL_PREFIX to
# a stringified variant of this prefix.

AC_DEFUN([gl_ASM_SYMBOL_PREFIX],
[
  AC_REQUIRE([AC_PROG_EGREP])
  dnl We don't use GCC's __USER_LABEL_PREFIX__ here, because
  dnl 1. It works only for GCC.
  dnl 2. It is incorrectly defined on some platforms, in some GCC versions.
  AC_REQUIRE([gl_C_ASM])
  AC_CACHE_CHECK(
    [whether C symbols are prefixed with underscore at the linker level],
    [gl_cv_prog_as_underscore],
    [cat > conftest.c <<EOF
#ifdef __cplusplus
extern "C" int foo (void);
#endif
int foo(void) { return 0; }
EOF
     # Look for the assembly language name in the .s file.
     AC_TRY_COMMAND(${CC-cc} $CFLAGS $CPPFLAGS $gl_c_asm_opt conftest.c) >/dev/null 2>&1
     if LC_ALL=C $EGREP '(^|[[^a-zA-Z0-9_]])_foo([[^a-zA-Z0-9_]]|$)' conftest.$gl_asmext >/dev/null; then
       gl_cv_prog_as_underscore=yes
     else
       gl_cv_prog_as_underscore=no
     fi
     rm -fr conftest*
    ])
  if test $gl_cv_prog_as_underscore = yes; then
    USER_LABEL_PREFIX=_
  else
    USER_LABEL_PREFIX=
  fi
  AC_DEFINE_UNQUOTED([USER_LABEL_PREFIX], [$USER_LABEL_PREFIX],
    [Define to the prefix of C symbols at the assembler and linker level,
     either an underscore or empty.])
  ASM_SYMBOL_PREFIX='"'${USER_LABEL_PREFIX}'"'
  AC_SUBST([ASM_SYMBOL_PREFIX])
])

# gl_C_ASM
# Determines how to produce an assembly language file from C source code.
# Sets the variables:
#   gl_asmext - the extension of assembly language output,
#   gl_c_asm_opt - the C compiler option that produces assembly language output.

AC_DEFUN([gl_C_ASM],
[
  AC_EGREP_CPP([MicrosoftCompiler],
    [
#ifdef _MSC_VER
MicrosoftCompiler
#endif
    ],
    [dnl Microsoft's 'cl' and 'clang-cl' produce an .asm file, whereas 'clang'
     dnl produces a .s file. Need to distinguish 'clang' and 'clang-cl'.
     rm -fr conftest*
     echo 'int dummy;' > conftest.c
     AC_TRY_COMMAND(${CC-cc} $CFLAGS $CPPFLAGS -c conftest.c) >/dev/null 2>&1
     if test -f conftest.o; then
       gl_asmext='s'
       gl_c_asm_opt='-S'
     else
       gl_asmext='asm'
       gl_c_asm_opt='-c -Fa'
     fi
     rm -fr conftest*
    ],
    [gl_asmext='s'
     gl_c_asm_opt='-S'
    ])
])
