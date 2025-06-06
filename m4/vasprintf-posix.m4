# vasprintf-posix.m4
# serial 21
dnl Copyright (C) 2007-2025 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

AC_DEFUN([gl_FUNC_VASPRINTF_POSIX],
[
  AC_REQUIRE([gl_FUNC_VASPRINTF_IS_POSIX])
  if test $gl_cv_func_vasprintf_posix = no; then
    gl_PREREQ_VASNPRINTF_WITH_POSIX_EXTRAS
    gl_REPLACE_VASNPRINTF
    gl_REPLACE_VASPRINTF
  fi
])

dnl Test whether vasprintf exists and is POSIX compliant.
dnl Result is gl_cv_func_vasprintf_posix.
AC_DEFUN([gl_FUNC_VASPRINTF_IS_POSIX],
[
  AC_REQUIRE([gl_PRINTF_SIZES_C99])
  AC_REQUIRE([gl_PRINTF_SIZES_C23])
  AC_REQUIRE([gl_PRINTF_LONG_DOUBLE])
  AC_REQUIRE([gl_PRINTF_INFINITE])
  AC_REQUIRE([gl_PRINTF_INFINITE_LONG_DOUBLE])
  AC_REQUIRE([gl_PRINTF_DIRECTIVE_A])
  AC_REQUIRE([gl_PRINTF_DIRECTIVE_B])
  AC_REQUIRE([gl_PRINTF_DIRECTIVE_F])
  m4_ifdef([gl_PRINTF_SUPPORT_N_DIRECTIVE],[AC_REQUIRE([gl_PRINTF_DIRECTIVE_N])])
  AC_REQUIRE([gl_PRINTF_DIRECTIVE_LS])
  AC_REQUIRE([gl_PRINTF_DIRECTIVE_LC])
  AC_REQUIRE([gl_PRINTF_POSITIONS])
  AC_REQUIRE([gl_PRINTF_FLAG_GROUPING])
  AC_REQUIRE([gl_PRINTF_FLAG_GROUPING_INT_PRECISION])
  AC_REQUIRE([gl_PRINTF_FLAG_GROUPING_MULTIBYTE])
  AC_REQUIRE([gl_PRINTF_FLAG_LEFTADJUST])
  AC_REQUIRE([gl_PRINTF_FLAG_ZERO])
  AC_REQUIRE([gl_PRINTF_FLAG_ALT_PRECISION_ZERO])
  AC_REQUIRE([gl_PRINTF_PRECISION])
  AC_REQUIRE([gl_PRINTF_ENOMEM])
  gl_cv_func_vasprintf_posix=no
  AC_CHECK_FUNCS([vasprintf])
  case "$gl_cv_func_printf_sizes_c99" in
    *yes)
      case "$gl_cv_func_printf_sizes_c23" in
        *yes)
          case "$gl_cv_func_printf_long_double" in
            *yes)
              case "$gl_cv_func_printf_infinite" in
                *yes)
                  case "$gl_cv_func_printf_infinite_long_double" in
                    *yes)
                      case "$gl_cv_func_printf_directive_a" in
                        *yes)
                          case "$gl_cv_func_printf_directive_b" in
                            *yes)
                              case "$gl_cv_func_printf_directive_f" in
                                *yes)
                                  case m4_ifdef([gl_PRINTF_SUPPORT_N_DIRECTIVE],["$gl_cv_func_printf_directive_n"],["yes"]) in
                                    *yes)
                                      case "$gl_cv_func_printf_directive_ls" in
                                        *yes)
                                          case "$gl_cv_func_printf_directive_lc" in
                                            *yes)
                                              case "$gl_cv_func_printf_positions" in
                                                *yes)
                                                  case "$gl_cv_func_printf_flag_grouping" in
                                                    *yes)
                                                      case "$gl_cv_func_printf_flag_grouping_int_precision" in
                                                        *yes)
                                                          case "$gl_cv_func_printf_flag_grouping_multibyte" in
                                                            *yes)
                                                              case "$gl_cv_func_printf_flag_leftadjust" in
                                                                *yes)
                                                                  case "$gl_cv_func_printf_flag_zero" in
                                                                    *yes)
                                                                      case "$gl_cv_func_printf_flag_alt_precision_zero" in
                                                                        *yes)
                                                                          case "$gl_cv_func_printf_precision" in
                                                                            *yes)
                                                                              case "$gl_cv_func_printf_enomem" in
                                                                                *yes)
                                                                                  if test $ac_cv_func_vasprintf = yes; then
                                                                                    # vasprintf exists and is
                                                                                    # already POSIX compliant.
                                                                                    gl_cv_func_vasprintf_posix=yes
                                                                                  fi
                                                                                  ;;
                                                                              esac
                                                                              ;;
                                                                          esac
                                                                          ;;
                                                                      esac
                                                                      ;;
                                                                  esac
                                                                  ;;
                                                              esac
                                                              ;;
                                                          esac
                                                          ;;
                                                      esac
                                                      ;;
                                                  esac
                                                  ;;
                                              esac
                                              ;;
                                          esac
                                          ;;
                                      esac
                                      ;;
                                  esac
                                  ;;
                              esac
                              ;;
                          esac
                          ;;
                      esac
                      ;;
                  esac
                  ;;
              esac
              ;;
          esac
          ;;
      esac
      ;;
  esac
])
