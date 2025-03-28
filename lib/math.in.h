/* A GNU-like <math.h>.

   Copyright (C) 2002-2003, 2007-2025 Free Software Foundation, Inc.

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

/* On Android, in C++ mode, when /usr/include/c++/v1/math.h is being included
   and /usr/include/math.h has not yet been included, skip this file, since it
   would lead to many syntax errors.  */
#if !(defined __ANDROID__ && defined _LIBCPP_MATH_H && !defined INFINITY)

#ifndef _@GUARD_PREFIX@_MATH_H

#if __GNUC__ >= 3
@PRAGMA_SYSTEM_HEADER@
#endif
@PRAGMA_COLUMNS@

#if defined _GL_INCLUDING_MATH_H
/* Special invocation convention:
   - On FreeBSD 12.2 we have a sequence of nested includes
     <math.h> -> <stdlib.h> -> <sys/wait.h> -> <sys/types.h> -> <sys/select.h>
       -> <signal.h> -> <pthread.h> -> <stdlib.h> -> <math.h>
     In this situation, the functions are not yet declared, therefore we cannot
     provide the C++ aliases.  */

#@INCLUDE_NEXT_AS_FIRST_DIRECTIVE@ @NEXT_AS_FIRST_DIRECTIVE_MATH_H@

#else
/* Normal invocation convention.  */

/* The include_next requires a split double-inclusion guard.  */
#define _GL_INCLUDING_MATH_H
#@INCLUDE_NEXT_AS_FIRST_DIRECTIVE@ @NEXT_AS_FIRST_DIRECTIVE_MATH_H@
#undef _GL_INCLUDING_MATH_H

#ifndef _@GUARD_PREFIX@_MATH_H
#define _@GUARD_PREFIX@_MATH_H

/* This file uses _GL_INLINE_HEADER_BEGIN, _GL_INLINE, _GL_ATTRIBUTE_CONST,
   GNULIB_POSIXCHECK, HAVE_RAW_DECL_*.  */
#if !_GL_CONFIG_H_INCLUDED
 #error "Please include config.h first."
#endif

/* On OpenVMS, NAN, INFINITY, and HUGEVAL macros are defined in <fp.h>.  */
#if defined __VMS && ! defined NAN
# include <fp.h>
#endif

_GL_INLINE_HEADER_BEGIN
#ifndef _GL_MATH_INLINE
# define _GL_MATH_INLINE _GL_INLINE
#endif

/* The __attribute__ feature is available in gcc versions 2.5 and later.
   The attribute __const__ was added in gcc 2.95.  */
#ifndef _GL_ATTRIBUTE_CONST
# if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95) || defined __clang__
#  define _GL_ATTRIBUTE_CONST __attribute__ ((__const__))
# else
#  define _GL_ATTRIBUTE_CONST /* empty */
# endif
#endif

/* The definitions of _GL_FUNCDECL_RPL etc. are copied here.  */

/* The definition of _GL_ARG_NONNULL is copied here.  */

/* The definition of _GL_WARN_ON_USE is copied here.  */

#ifdef __cplusplus
/* Helper macros to define type-generic function FUNC as overloaded functions,
   rather than as macros like in C.  POSIX declares these with an argument of
   real-floating (that is, one of float, double, or long double).  */
# define _GL_MATH_CXX_REAL_FLOATING_DECL_1(func) \
static inline int                                                   \
_gl_cxx_ ## func ## f (float f)                                     \
{                                                                   \
  return func (f);                                                  \
}                                                                   \
static inline int                                                   \
_gl_cxx_ ## func ## d (double d)                                    \
{                                                                   \
  return func (d);                                                  \
}                                                                   \
static inline int                                                   \
_gl_cxx_ ## func ## l (long double l)                               \
{                                                                   \
  return func (l);                                                  \
}
# define _GL_MATH_CXX_REAL_FLOATING_DECL_2(func,rpl_func,rettype) \
_GL_BEGIN_NAMESPACE                                                 \
inline rettype                                                      \
rpl_func (float f)                                                  \
{                                                                   \
  return _gl_cxx_ ## func ## f (f);                                 \
}                                                                   \
inline rettype                                                      \
rpl_func (double d)                                                 \
{                                                                   \
  return _gl_cxx_ ## func ## d (d);                                 \
}                                                                   \
inline rettype                                                      \
rpl_func (long double l)                                            \
{                                                                   \
  return _gl_cxx_ ## func ## l (l);                                 \
}                                                                   \
_GL_END_NAMESPACE
#endif

/* Helper macros to define a portability warning for the
   classification macro FUNC called with VALUE.  POSIX declares the
   classification macros with an argument of real-floating (that is,
   one of float, double, or long double).  */
#define _GL_WARN_REAL_FLOATING_DECL(func) \
_GL_MATH_INLINE int                                                       \
_GL_WARN_ON_USE_ATTRIBUTE (#func " is unportable - "                      \
                           "use gnulib module " #func " for portability") \
rpl_ ## func ## f (float f)                                               \
{                                                                         \
  return func (f);                                                        \
}                                                                         \
_GL_MATH_INLINE int                                                       \
_GL_WARN_ON_USE_ATTRIBUTE (#func " is unportable - "                      \
                           "use gnulib module " #func " for portability") \
rpl_ ## func ## d (double d)                                              \
{                                                                         \
  return func (d);                                                        \
}                                                                         \
_GL_MATH_INLINE int                                                       \
_GL_WARN_ON_USE_ATTRIBUTE (#func " is unportable - "                      \
                           "use gnulib module " #func " for portability") \
rpl_ ## func ## l (long double l)                                         \
{                                                                         \
  return func (l);                                                        \
}
#define _GL_WARN_REAL_FLOATING_IMPL(func, value) \
  (sizeof (value) == sizeof (float) ? rpl_ ## func ## f (value)     \
   : sizeof (value) == sizeof (double) ? rpl_ ## func ## d (value)  \
   : rpl_ ## func ## l (value))


#if @REPLACE_ITOLD@
/* Pull in a function that fixes the 'int' to 'long double' conversion
   of glibc 2.7.  */
_GL_EXTERN_C void _Qp_itoq (long double *, int);
static void (*_gl_math_fix_itold) (long double *, int) = _Qp_itoq;
#endif


/* Ensure that INFINITY is a constant expression, of type 'float'.  */
#if !defined INFINITY || (defined __FreeBSD__ && __FreeBSD__ < 8) || defined _AIX || defined __MINGW32__
# undef INFINITY
# if defined __GNUC__ || defined __clang__
#  define INFINITY (__builtin_inff ())
# else
#  define INFINITY (1.0f / 0.0f)
# endif
#endif

/* POSIX allows platforms that don't support NAN.  But all major
   machines in the past 15 years have supported something close to
   IEEE NaN, so we define this unconditionally.  We also must define
   it on platforms like Solaris 10, where NAN is present but defined
   as a function pointer rather than a floating point constant.
   Also ensure that it is a constant expression, of type 'float'.  */
#if !defined NAN || @REPLACE_NAN@ || (defined __FreeBSD__ && __FreeBSD__ < 8) || defined _AIX || defined __MINGW32__
# if !GNULIB_defined_NAN
#  undef NAN
  /* The Compaq (ex-DEC) C 6.4 compiler and the Microsoft MSVC 9 compiler
     choke on the expression 0.0 / 0.0.  */
#  if defined __DECC || defined _MSC_VER
_GL_MATH_INLINE float
_NaN ()
{
  static float zero = 0.0f;
  return zero / zero;
}
#   define NAN (_NaN())
#  elif defined __GNUC__ || defined __clang__
#   define NAN (__builtin_nanf (""))
#  else
#   define NAN (0.0f / 0.0f)
#  endif
#  define GNULIB_defined_NAN 1
# endif
#endif

/* Solaris 10 defines HUGE_VAL, but as a function pointer rather
   than a floating point constant.  */
#if @REPLACE_HUGE_VAL@
# undef HUGE_VALF
# define HUGE_VALF (1.0f / 0.0f)
# undef HUGE_VAL
# define HUGE_VAL (1.0 / 0.0)
# undef HUGE_VALL
# define HUGE_VALL (1.0L / 0.0L)
#endif

/* HUGE_VALF is a 'float' Infinity.  */
#if !defined HUGE_VALF || (defined __FreeBSD__ && __FreeBSD__ < 6)
# undef HUGE_VALF
# if defined _MSC_VER
/* The Microsoft MSVC 9 compiler chokes on the expression 1.0f / 0.0f.  */
#  define HUGE_VALF (1e25f * 1e25f)
# elif defined __GNUC__ || defined __clang__
#  define HUGE_VALF (__builtin_inff ())
# else
#  define HUGE_VALF (1.0f / 0.0f)
# endif
#endif

/* HUGE_VAL is a 'double' Infinity.  */
#if !defined HUGE_VAL || (defined __FreeBSD__ && __FreeBSD__ < 6) || defined _AIX
# undef HUGE_VAL
# if defined _MSC_VER
/* The Microsoft MSVC 9 compiler chokes on the expression 1.0 / 0.0.  */
#  define HUGE_VAL (1e250 * 1e250)
# elif defined __GNUC__ || defined __clang__
#  define HUGE_VAL (__builtin_inf ())
# else
#  define HUGE_VAL (1.0 / 0.0)
# endif
#endif

/* HUGE_VALL is a 'long double' Infinity.  */
#if !defined HUGE_VALL || (defined __FreeBSD__ && __FreeBSD__ < 6) || defined _AIX
# undef HUGE_VALL
# if defined _MSC_VER
/* The Microsoft MSVC 9 compiler chokes on the expression 1.0L / 0.0L.  */
#  define HUGE_VALL (1e250L * 1e250L)
# elif defined __GNUC__ || defined __clang__
#  define HUGE_VALL (__builtin_infl ())
# else
#  define HUGE_VALL (1.0L / 0.0L)
# endif
#endif


#if !(defined FP_ILOGB0 && defined FP_ILOGBNAN)
 /* Ensure FP_ILOGB0 and FP_ILOGBNAN are defined.  */
# if defined __NetBSD__ || defined __sgi
  /* NetBSD, IRIX 6.5: match what ilogb() does */
#  define FP_ILOGB0   (- 2147483647 - 1) /* INT_MIN */
#  define FP_ILOGBNAN (- 2147483647 - 1) /* INT_MIN */
# elif defined _AIX
  /* AIX 5.1: match what ilogb() does in AIX >= 5.2 */
#  define FP_ILOGB0   (- 2147483647 - 1) /* INT_MIN */
#  define FP_ILOGBNAN 2147483647 /* INT_MAX */
# elif defined __sun
  /* Solaris 9: match what ilogb() does */
#  define FP_ILOGB0   (- 2147483647) /* - INT_MAX */
#  define FP_ILOGBNAN 2147483647 /* INT_MAX */
# else
  /* Gnulib defined values.  */
#  define FP_ILOGB0   (- 2147483647) /* - INT_MAX */
#  define FP_ILOGBNAN (- 2147483647 - 1) /* INT_MIN */
# endif
#endif


#if @GNULIB_ACOSF@
# if @REPLACE_ACOSF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef acosf
#   define acosf rpl_acosf
#  endif
_GL_FUNCDECL_RPL (acosf, float, (float x), );
_GL_CXXALIAS_RPL (acosf, float, (float x));
# else
#  if !@HAVE_ACOSF@
#   undef acosf
_GL_FUNCDECL_SYS (acosf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (acosf, float, (float x));
# endif
_GL_CXXALIASWARN (acosf);
#elif defined GNULIB_POSIXCHECK
# undef acosf
# if HAVE_RAW_DECL_ACOSF
_GL_WARN_ON_USE (acosf, "acosf is unportable - "
                 "use gnulib module acosf for portability");
# endif
#endif

#if @GNULIB_ACOSL@
# if !@HAVE_ACOSL@ || !@HAVE_DECL_ACOSL@
#  undef acosl
_GL_FUNCDECL_SYS (acosl, long double, (long double x), );
# endif
_GL_CXXALIAS_SYS (acosl, long double, (long double x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (acosl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef acosl
# if HAVE_RAW_DECL_ACOSL
_GL_WARN_ON_USE (acosl, "acosl is unportable - "
                 "use gnulib module acosl for portability");
# endif
#endif


#if @GNULIB_ASINF@
# if @REPLACE_ASINF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef asinf
#   define asinf rpl_asinf
#  endif
_GL_FUNCDECL_RPL (asinf, float, (float x), );
_GL_CXXALIAS_RPL (asinf, float, (float x));
# else
#  if !@HAVE_ASINF@
#   undef asinf
_GL_FUNCDECL_SYS (asinf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (asinf, float, (float x));
# endif
_GL_CXXALIASWARN (asinf);
#elif defined GNULIB_POSIXCHECK
# undef asinf
# if HAVE_RAW_DECL_ASINF
_GL_WARN_ON_USE (asinf, "asinf is unportable - "
                 "use gnulib module asinf for portability");
# endif
#endif

#if @GNULIB_ASINL@
# if !@HAVE_ASINL@ || !@HAVE_DECL_ASINL@
#  undef asinl
_GL_FUNCDECL_SYS (asinl, long double, (long double x), );
# endif
_GL_CXXALIAS_SYS (asinl, long double, (long double x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (asinl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef asinl
# if HAVE_RAW_DECL_ASINL
_GL_WARN_ON_USE (asinl, "asinl is unportable - "
                 "use gnulib module asinl for portability");
# endif
#endif


#if @GNULIB_ATANF@
# if @REPLACE_ATANF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef atanf
#   define atanf rpl_atanf
#  endif
_GL_FUNCDECL_RPL (atanf, float, (float x), );
_GL_CXXALIAS_RPL (atanf, float, (float x));
# else
#  if !@HAVE_ATANF@
#   undef atanf
_GL_FUNCDECL_SYS (atanf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (atanf, float, (float x));
# endif
_GL_CXXALIASWARN (atanf);
#elif defined GNULIB_POSIXCHECK
# undef atanf
# if HAVE_RAW_DECL_ATANF
_GL_WARN_ON_USE (atanf, "atanf is unportable - "
                 "use gnulib module atanf for portability");
# endif
#endif

#if @GNULIB_ATANL@
# if !@HAVE_ATANL@ || !@HAVE_DECL_ATANL@
#  undef atanl
_GL_FUNCDECL_SYS (atanl, long double, (long double x), );
# endif
_GL_CXXALIAS_SYS (atanl, long double, (long double x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (atanl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef atanl
# if HAVE_RAW_DECL_ATANL
_GL_WARN_ON_USE (atanl, "atanl is unportable - "
                 "use gnulib module atanl for portability");
# endif
#endif


#if @GNULIB_ATAN2F@
# if @REPLACE_ATAN2F@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef atan2f
#   define atan2f rpl_atan2f
#  endif
_GL_FUNCDECL_RPL (atan2f, float, (float y, float x), );
_GL_CXXALIAS_RPL (atan2f, float, (float y, float x));
# else
#  if !@HAVE_ATAN2F@
#   undef atan2f
_GL_FUNCDECL_SYS (atan2f, float, (float y, float x), );
#  endif
_GL_CXXALIAS_SYS (atan2f, float, (float y, float x));
# endif
_GL_CXXALIASWARN (atan2f);
#elif defined GNULIB_POSIXCHECK
# undef atan2f
# if HAVE_RAW_DECL_ATAN2F
_GL_WARN_ON_USE (atan2f, "atan2f is unportable - "
                 "use gnulib module atan2f for portability");
# endif
#endif


#if @GNULIB_CBRTF@
# if @REPLACE_CBRTF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef cbrtf
#   define cbrtf rpl_cbrtf
#  endif
_GL_FUNCDECL_RPL (cbrtf, float, (float x), );
_GL_CXXALIAS_RPL (cbrtf, float, (float x));
# else
#  if !@HAVE_DECL_CBRTF@
_GL_FUNCDECL_SYS (cbrtf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (cbrtf, float, (float x));
# endif
_GL_CXXALIASWARN (cbrtf);
#elif defined GNULIB_POSIXCHECK
# undef cbrtf
# if HAVE_RAW_DECL_CBRTF
_GL_WARN_ON_USE (cbrtf, "cbrtf is unportable - "
                 "use gnulib module cbrtf for portability");
# endif
#endif

#if @GNULIB_CBRT@
# if !@HAVE_CBRT@
_GL_FUNCDECL_SYS (cbrt, double, (double x), );
# endif
_GL_CXXALIAS_SYS (cbrt, double, (double x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (cbrt, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef cbrt
# if HAVE_RAW_DECL_CBRT
_GL_WARN_ON_USE (cbrt, "cbrt is unportable - "
                 "use gnulib module cbrt for portability");
# endif
#endif

#if @GNULIB_CBRTL@
# if @REPLACE_CBRTL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef cbrtl
#   define cbrtl rpl_cbrtl
#  endif
_GL_FUNCDECL_RPL (cbrtl, long double, (long double x), );
_GL_CXXALIAS_RPL (cbrtl, long double, (long double x));
# else
#  if !@HAVE_DECL_CBRTL@
_GL_FUNCDECL_SYS (cbrtl, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (cbrtl, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (cbrtl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef cbrtl
# if HAVE_RAW_DECL_CBRTL
_GL_WARN_ON_USE (cbrtl, "cbrtl is unportable - "
                 "use gnulib module cbrtl for portability");
# endif
#endif


#if @GNULIB_CEILF@
# if @REPLACE_CEILF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef ceilf
#   define ceilf rpl_ceilf
#  endif
_GL_FUNCDECL_RPL (ceilf, float, (float x), );
_GL_CXXALIAS_RPL (ceilf, float, (float x));
# else
#  if !@HAVE_DECL_CEILF@
#   undef ceilf
_GL_FUNCDECL_SYS (ceilf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (ceilf, float, (float x));
# endif
_GL_CXXALIASWARN (ceilf);
#elif defined GNULIB_POSIXCHECK
# undef ceilf
# if HAVE_RAW_DECL_CEILF
_GL_WARN_ON_USE (ceilf, "ceilf is unportable - "
                 "use gnulib module ceilf for portability");
# endif
#endif

#if @GNULIB_CEIL@
# if @REPLACE_CEIL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef ceil
#   define ceil rpl_ceil
#  endif
_GL_FUNCDECL_RPL (ceil, double, (double x), );
_GL_CXXALIAS_RPL (ceil, double, (double x));
# else
_GL_CXXALIAS_SYS (ceil, double, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (ceil, double, (double x));
# endif
#endif

#if @GNULIB_CEILL@
# if @REPLACE_CEILL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef ceill
#   define ceill rpl_ceill
#  endif
_GL_FUNCDECL_RPL (ceill, long double, (long double x), );
_GL_CXXALIAS_RPL (ceill, long double, (long double x));
# else
#  if !@HAVE_DECL_CEILL@
#   undef ceill
_GL_FUNCDECL_SYS (ceill, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (ceill, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (ceill);
# endif
#elif defined GNULIB_POSIXCHECK
# undef ceill
# if HAVE_RAW_DECL_CEILL
_GL_WARN_ON_USE (ceill, "ceill is unportable - "
                 "use gnulib module ceill for portability");
# endif
#endif


#if @GNULIB_COPYSIGNF@
# if !@HAVE_DECL_COPYSIGNF@
#  undef copysignf
_GL_FUNCDECL_SYS (copysignf, float, (float x, float y), );
# endif
_GL_CXXALIAS_SYS (copysignf, float, (float x, float y));
_GL_CXXALIASWARN (copysignf);
#elif defined GNULIB_POSIXCHECK
# undef copysignf
# if HAVE_RAW_DECL_COPYSIGNF
_GL_WARN_ON_USE (copysignf, "copysignf is unportable - "
                 "use gnulib module copysignf for portability");
# endif
#endif

#if @GNULIB_COPYSIGN@
# if !@HAVE_COPYSIGN@
_GL_FUNCDECL_SYS (copysign, double, (double x, double y), );
# endif
_GL_CXXALIAS_SYS (copysign, double, (double x, double y));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (copysign, double, (double x, double y));
# endif
#elif defined GNULIB_POSIXCHECK
# undef copysign
# if HAVE_RAW_DECL_COPYSIGN
_GL_WARN_ON_USE (copysign, "copysign is unportable - "
                 "use gnulib module copysign for portability");
# endif
#endif

#if @GNULIB_COPYSIGNL@
# if !@HAVE_COPYSIGNL@
_GL_FUNCDECL_SYS (copysignl, long double, (long double x, long double y), );
# endif
_GL_CXXALIAS_SYS (copysignl, long double, (long double x, long double y));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (copysignl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef copysignl
# if HAVE_RAW_DECL_COPYSIGNL
_GL_WARN_ON_USE (copysign, "copysignl is unportable - "
                 "use gnulib module copysignl for portability");
# endif
#endif


#if @GNULIB_COSF@
# if @REPLACE_COSF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef cosf
#   define cosf rpl_cosf
#  endif
_GL_FUNCDECL_RPL (cosf, float, (float x), );
_GL_CXXALIAS_RPL (cosf, float, (float x));
# else
#  if !@HAVE_COSF@
#   undef cosf
_GL_FUNCDECL_SYS (cosf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (cosf, float, (float x));
# endif
_GL_CXXALIASWARN (cosf);
#elif defined GNULIB_POSIXCHECK
# undef cosf
# if HAVE_RAW_DECL_COSF
_GL_WARN_ON_USE (cosf, "cosf is unportable - "
                 "use gnulib module cosf for portability");
# endif
#endif

#if @GNULIB_COSL@
# if !@HAVE_COSL@ || !@HAVE_DECL_COSL@
#  undef cosl
_GL_FUNCDECL_SYS (cosl, long double, (long double x), );
# endif
_GL_CXXALIAS_SYS (cosl, long double, (long double x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (cosl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef cosl
# if HAVE_RAW_DECL_COSL
_GL_WARN_ON_USE (cosl, "cosl is unportable - "
                 "use gnulib module cosl for portability");
# endif
#endif


#if @GNULIB_COSHF@
# if @REPLACE_COSHF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef coshf
#   define coshf rpl_coshf
#  endif
_GL_FUNCDECL_RPL (coshf, float, (float x), );
_GL_CXXALIAS_RPL (coshf, float, (float x));
# else
#  if !@HAVE_COSHF@
#   undef coshf
_GL_FUNCDECL_SYS (coshf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (coshf, float, (float x));
# endif
_GL_CXXALIASWARN (coshf);
#elif defined GNULIB_POSIXCHECK
# undef coshf
# if HAVE_RAW_DECL_COSHF
_GL_WARN_ON_USE (coshf, "coshf is unportable - "
                 "use gnulib module coshf for portability");
# endif
#endif


#if @GNULIB_EXPF@
# if @REPLACE_EXPF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef expf
#   define expf rpl_expf
#  endif
_GL_FUNCDECL_RPL (expf, float, (float x), );
_GL_CXXALIAS_RPL (expf, float, (float x));
# else
#  if !@HAVE_EXPF@
#   undef expf
_GL_FUNCDECL_SYS (expf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (expf, float, (float x));
# endif
_GL_CXXALIASWARN (expf);
#elif defined GNULIB_POSIXCHECK
# undef expf
# if HAVE_RAW_DECL_EXPF
_GL_WARN_ON_USE (expf, "expf is unportable - "
                 "use gnulib module expf for portability");
# endif
#endif

#if @GNULIB_EXPL@
# if @REPLACE_EXPL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef expl
#   define expl rpl_expl
#  endif
_GL_FUNCDECL_RPL (expl, long double, (long double x), );
_GL_CXXALIAS_RPL (expl, long double, (long double x));
# else
#  if !@HAVE_EXPL@ || !@HAVE_DECL_EXPL@
#   undef expl
_GL_FUNCDECL_SYS (expl, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (expl, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (expl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef expl
# if HAVE_RAW_DECL_EXPL
_GL_WARN_ON_USE (expl, "expl is unportable - "
                 "use gnulib module expl for portability");
# endif
#endif


#if @GNULIB_EXP2F@
# if !@HAVE_DECL_EXP2F@
_GL_FUNCDECL_SYS (exp2f, float, (float x), );
# endif
_GL_CXXALIAS_SYS (exp2f, float, (float x));
_GL_CXXALIASWARN (exp2f);
#elif defined GNULIB_POSIXCHECK
# undef exp2f
# if HAVE_RAW_DECL_EXP2F
_GL_WARN_ON_USE (exp2f, "exp2f is unportable - "
                 "use gnulib module exp2f for portability");
# endif
#endif

#if @GNULIB_EXP2@
# if @REPLACE_EXP2@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef exp2
#   define exp2 rpl_exp2
#  endif
_GL_FUNCDECL_RPL (exp2, double, (double x), );
_GL_CXXALIAS_RPL (exp2, double, (double x));
# else
#  if !@HAVE_DECL_EXP2@
_GL_FUNCDECL_SYS (exp2, double, (double x), );
#  endif
_GL_CXXALIAS_SYS (exp2, double, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (exp2, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef exp2
# if HAVE_RAW_DECL_EXP2
_GL_WARN_ON_USE (exp2, "exp2 is unportable - "
                 "use gnulib module exp2 for portability");
# endif
#endif

#if @GNULIB_EXP2L@
# if @REPLACE_EXP2L@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef exp2l
#   define exp2l rpl_exp2l
#  endif
_GL_FUNCDECL_RPL (exp2l, long double, (long double x), );
_GL_CXXALIAS_RPL (exp2l, long double, (long double x));
# else
#  if !@HAVE_DECL_EXP2L@
#   undef exp2l
_GL_FUNCDECL_SYS (exp2l, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (exp2l, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (exp2l);
# endif
#elif defined GNULIB_POSIXCHECK
# undef exp2l
# if HAVE_RAW_DECL_EXP2L
_GL_WARN_ON_USE (exp2l, "exp2l is unportable - "
                 "use gnulib module exp2l for portability");
# endif
#endif


#if @GNULIB_EXPM1F@
# if @REPLACE_EXPM1F@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef expm1f
#   define expm1f rpl_expm1f
#  endif
_GL_FUNCDECL_RPL (expm1f, float, (float x), );
_GL_CXXALIAS_RPL (expm1f, float, (float x));
# else
#  if !@HAVE_EXPM1F@
_GL_FUNCDECL_SYS (expm1f, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (expm1f, float, (float x));
# endif
_GL_CXXALIASWARN (expm1f);
#elif defined GNULIB_POSIXCHECK
# undef expm1f
# if HAVE_RAW_DECL_EXPM1F
_GL_WARN_ON_USE (expm1f, "expm1f is unportable - "
                 "use gnulib module expm1f for portability");
# endif
#endif

#if @GNULIB_EXPM1@
# if @REPLACE_EXPM1@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef expm1
#   define expm1 rpl_expm1
#  endif
_GL_FUNCDECL_RPL (expm1, double, (double x), );
_GL_CXXALIAS_RPL (expm1, double, (double x));
# else
#  if !@HAVE_EXPM1@
_GL_FUNCDECL_SYS (expm1, double, (double x), );
#  endif
_GL_CXXALIAS_SYS (expm1, double, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (expm1, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef expm1
# if HAVE_RAW_DECL_EXPM1
_GL_WARN_ON_USE (expm1, "expm1 is unportable - "
                 "use gnulib module expm1 for portability");
# endif
#endif

#if @GNULIB_EXPM1L@
# if @REPLACE_EXPM1L@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef expm1l
#   define expm1l rpl_expm1l
#  endif
_GL_FUNCDECL_RPL (expm1l, long double, (long double x), );
_GL_CXXALIAS_RPL (expm1l, long double, (long double x));
# else
#  if !@HAVE_DECL_EXPM1L@
#   undef expm1l
#   if !(defined __cplusplus && defined _AIX)
_GL_FUNCDECL_SYS (expm1l, long double, (long double x), );
#   endif
#  endif
_GL_CXXALIAS_SYS (expm1l, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (expm1l);
# endif
#elif defined GNULIB_POSIXCHECK
# undef expm1l
# if HAVE_RAW_DECL_EXPM1L
_GL_WARN_ON_USE (expm1l, "expm1l is unportable - "
                 "use gnulib module expm1l for portability");
# endif
#endif


#if @GNULIB_FABSF@
# if !@HAVE_FABSF@
#  undef fabsf
_GL_FUNCDECL_SYS (fabsf, float, (float x), );
# endif
_GL_CXXALIAS_SYS (fabsf, float, (float x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (fabsf);
# endif
#elif defined GNULIB_POSIXCHECK
# undef fabsf
# if HAVE_RAW_DECL_FABSF
_GL_WARN_ON_USE (fabsf, "fabsf is unportable - "
                 "use gnulib module fabsf for portability");
# endif
#endif

#if @GNULIB_FABSL@
# if @REPLACE_FABSL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef fabsl
#   define fabsl rpl_fabsl
#  endif
_GL_FUNCDECL_RPL (fabsl, long double, (long double x), );
_GL_CXXALIAS_RPL (fabsl, long double, (long double x));
# else
#  if !@HAVE_FABSL@
#   undef fabsl
_GL_FUNCDECL_SYS (fabsl, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (fabsl, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (fabsl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef fabsl
# if HAVE_RAW_DECL_FABSL
_GL_WARN_ON_USE (fabsl, "fabsl is unportable - "
                 "use gnulib module fabsl for portability");
# endif
#endif


#if @GNULIB_FLOORF@
# if @REPLACE_FLOORF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef floorf
#   define floorf rpl_floorf
#  endif
_GL_FUNCDECL_RPL (floorf, float, (float x), );
_GL_CXXALIAS_RPL (floorf, float, (float x));
# else
#  if !@HAVE_DECL_FLOORF@
#   undef floorf
_GL_FUNCDECL_SYS (floorf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (floorf, float, (float x));
# endif
_GL_CXXALIASWARN (floorf);
#elif defined GNULIB_POSIXCHECK
# undef floorf
# if HAVE_RAW_DECL_FLOORF
_GL_WARN_ON_USE (floorf, "floorf is unportable - "
                 "use gnulib module floorf for portability");
# endif
#endif

#if @GNULIB_FLOOR@
# if @REPLACE_FLOOR@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef floor
#   define floor rpl_floor
#  endif
_GL_FUNCDECL_RPL (floor, double, (double x), );
_GL_CXXALIAS_RPL (floor, double, (double x));
# else
_GL_CXXALIAS_SYS (floor, double, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (floor, double, (double x));
# endif
#endif

#if @GNULIB_FLOORL@
# if @REPLACE_FLOORL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef floorl
#   define floorl rpl_floorl
#  endif
_GL_FUNCDECL_RPL (floorl, long double, (long double x), );
_GL_CXXALIAS_RPL (floorl, long double, (long double x));
# else
#  if !@HAVE_DECL_FLOORL@
#   undef floorl
_GL_FUNCDECL_SYS (floorl, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (floorl, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (floorl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef floorl
# if HAVE_RAW_DECL_FLOORL
_GL_WARN_ON_USE (floorl, "floorl is unportable - "
                 "use gnulib module floorl for portability");
# endif
#endif


#if @GNULIB_FMAF@
# if @REPLACE_FMAF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef fmaf
#   define fmaf rpl_fmaf
#  endif
_GL_FUNCDECL_RPL (fmaf, float, (float x, float y, float z), );
_GL_CXXALIAS_RPL (fmaf, float, (float x, float y, float z));
# else
#  if !@HAVE_FMAF@
#   undef fmaf
_GL_FUNCDECL_SYS (fmaf, float, (float x, float y, float z), );
#  endif
_GL_CXXALIAS_SYS (fmaf, float, (float x, float y, float z));
# endif
_GL_CXXALIASWARN (fmaf);
#elif defined GNULIB_POSIXCHECK
# undef fmaf
# if HAVE_RAW_DECL_FMAF
_GL_WARN_ON_USE (fmaf, "fmaf is unportable - "
                 "use gnulib module fmaf for portability");
# endif
#endif

#if @GNULIB_FMA@
# if @REPLACE_FMA@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef fma
#   define fma rpl_fma
#  endif
_GL_FUNCDECL_RPL (fma, double, (double x, double y, double z), );
_GL_CXXALIAS_RPL (fma, double, (double x, double y, double z));
# else
#  if !@HAVE_FMA@
#   undef fma
_GL_FUNCDECL_SYS (fma, double, (double x, double y, double z), );
#  endif
_GL_CXXALIAS_SYS (fma, double, (double x, double y, double z));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (fma, double, (double x, double y, double z));
# endif
#elif defined GNULIB_POSIXCHECK
# undef fma
# if HAVE_RAW_DECL_FMA
_GL_WARN_ON_USE (fma, "fma is unportable - "
                 "use gnulib module fma for portability");
# endif
#endif

#if @GNULIB_FMAL@
# if @REPLACE_FMAL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef fmal
#   define fmal rpl_fmal
#  endif
_GL_FUNCDECL_RPL (fmal, long double,
                  (long double x, long double y, long double z), );
_GL_CXXALIAS_RPL (fmal, long double,
                  (long double x, long double y, long double z));
# else
#  if !@HAVE_FMAL@
#   undef fmal
#   if !(defined __cplusplus && defined _AIX)
_GL_FUNCDECL_SYS (fmal, long double,
                  (long double x, long double y, long double z), );
#   endif
#  endif
_GL_CXXALIAS_SYS (fmal, long double,
                  (long double x, long double y, long double z));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (fmal);
# endif
#elif defined GNULIB_POSIXCHECK
# undef fmal
# if HAVE_RAW_DECL_FMAL
_GL_WARN_ON_USE (fmal, "fmal is unportable - "
                 "use gnulib module fmal for portability");
# endif
#endif


#if @GNULIB_FMODF@
# if @REPLACE_FMODF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef fmodf
#   define fmodf rpl_fmodf
#  endif
_GL_FUNCDECL_RPL (fmodf, float, (float x, float y), );
_GL_CXXALIAS_RPL (fmodf, float, (float x, float y));
# else
#  if !@HAVE_FMODF@
#   undef fmodf
_GL_FUNCDECL_SYS (fmodf, float, (float x, float y), );
#  endif
_GL_CXXALIAS_SYS (fmodf, float, (float x, float y));
# endif
_GL_CXXALIASWARN (fmodf);
#elif defined GNULIB_POSIXCHECK
# undef fmodf
# if HAVE_RAW_DECL_FMODF
_GL_WARN_ON_USE (fmodf, "fmodf is unportable - "
                 "use gnulib module fmodf for portability");
# endif
#endif

#if @GNULIB_FMOD@
# if @REPLACE_FMOD@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef fmod
#   define fmod rpl_fmod
#  endif
_GL_FUNCDECL_RPL (fmod, double, (double x, double y), );
_GL_CXXALIAS_RPL (fmod, double, (double x, double y));
# else
_GL_CXXALIAS_SYS (fmod, double, (double x, double y));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (fmod, double, (double x, double y));
# endif
#elif defined GNULIB_POSIXCHECK
# undef fmod
# if HAVE_RAW_DECL_FMOD
_GL_WARN_ON_USE (fmod, "fmod has portability problems - "
                 "use gnulib module fmod for portability");
# endif
#endif

#if @GNULIB_FMODL@
# if @REPLACE_FMODL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef fmodl
#   define fmodl rpl_fmodl
#  endif
_GL_FUNCDECL_RPL (fmodl, long double, (long double x, long double y), );
_GL_CXXALIAS_RPL (fmodl, long double, (long double x, long double y));
# else
#  if !@HAVE_FMODL@
#   undef fmodl
_GL_FUNCDECL_SYS (fmodl, long double, (long double x, long double y), );
#  endif
_GL_CXXALIAS_SYS (fmodl, long double, (long double x, long double y));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (fmodl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef fmodl
# if HAVE_RAW_DECL_FMODL
_GL_WARN_ON_USE (fmodl, "fmodl is unportable - "
                 "use gnulib module fmodl for portability");
# endif
#endif


/* Write x as
     x = mantissa * 2^exp
   where
     If x finite and nonzero: 0.5 <= |mantissa| < 1.0.
     If x is zero: mantissa = x, exp = 0.
     If x is infinite or NaN: mantissa = x, exp unspecified.
   Store exp in *EXPPTR and return mantissa.  */
#if @GNULIB_FREXPF@
# if @REPLACE_FREXPF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef frexpf
#   define frexpf rpl_frexpf
#  endif
_GL_FUNCDECL_RPL (frexpf, float, (float x, int *expptr), _GL_ARG_NONNULL ((2)));
_GL_CXXALIAS_RPL (frexpf, float, (float x, int *expptr));
# else
#  if !@HAVE_FREXPF@
#   undef frexpf
_GL_FUNCDECL_SYS (frexpf, float, (float x, int *expptr), _GL_ARG_NONNULL ((2)));
#  endif
_GL_CXXALIAS_SYS (frexpf, float, (float x, int *expptr));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (frexpf);
# endif
#elif defined GNULIB_POSIXCHECK
# undef frexpf
# if HAVE_RAW_DECL_FREXPF
_GL_WARN_ON_USE (frexpf, "frexpf is unportable - "
                 "use gnulib module frexpf for portability");
# endif
#endif

/* Write x as
     x = mantissa * 2^exp
   where
     If x finite and nonzero: 0.5 <= |mantissa| < 1.0.
     If x is zero: mantissa = x, exp = 0.
     If x is infinite or NaN: mantissa = x, exp unspecified.
   Store exp in *EXPPTR and return mantissa.  */
#if @GNULIB_FREXP@
# if @REPLACE_FREXP@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef frexp
#   define frexp rpl_frexp
#  endif
_GL_FUNCDECL_RPL (frexp, double, (double x, int *expptr),
                                 _GL_ARG_NONNULL ((2)));
_GL_CXXALIAS_RPL (frexp, double, (double x, int *expptr));
# else
_GL_CXXALIAS_SYS (frexp, double, (double x, int *expptr));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (frexp, double, (double x, int *expptr));
# endif
#elif defined GNULIB_POSIXCHECK
# undef frexp
/* Assume frexp is always declared.  */
_GL_WARN_ON_USE (frexp, "frexp is unportable - "
                 "use gnulib module frexp for portability");
#endif

/* Write x as
     x = mantissa * 2^exp
   where
     If x finite and nonzero: 0.5 <= |mantissa| < 1.0.
     If x is zero: mantissa = x, exp = 0.
     If x is infinite or NaN: mantissa = x, exp unspecified.
   Store exp in *EXPPTR and return mantissa.  */
#if @GNULIB_FREXPL@ && @REPLACE_FREXPL@
# if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#  undef frexpl
#  define frexpl rpl_frexpl
# endif
_GL_FUNCDECL_RPL (frexpl, long double,
                  (long double x, int *expptr), _GL_ARG_NONNULL ((2)));
_GL_CXXALIAS_RPL (frexpl, long double, (long double x, int *expptr));
#else
# if !@HAVE_DECL_FREXPL@
_GL_FUNCDECL_SYS (frexpl, long double,
                  (long double x, int *expptr), _GL_ARG_NONNULL ((2)));
# endif
# if @GNULIB_FREXPL@
_GL_CXXALIAS_SYS (frexpl, long double, (long double x, int *expptr));
# endif
#endif
#if @GNULIB_FREXPL@ && !(@REPLACE_FREXPL@ && !@HAVE_DECL_FREXPL@)
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (frexpl);
# endif
#endif
#if !@GNULIB_FREXPL@ && defined GNULIB_POSIXCHECK
# undef frexpl
# if HAVE_RAW_DECL_FREXPL
_GL_WARN_ON_USE (frexpl, "frexpl is unportable - "
                 "use gnulib module frexpl for portability");
# endif
#endif


/* Return sqrt(x^2+y^2).  */
#if @GNULIB_HYPOTF@
# if @REPLACE_HYPOTF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef hypotf
#   define hypotf rpl_hypotf
#  endif
_GL_FUNCDECL_RPL (hypotf, float, (float x, float y), );
_GL_CXXALIAS_RPL (hypotf, float, (float x, float y));
# else
#  if !@HAVE_HYPOTF@
_GL_FUNCDECL_SYS (hypotf, float, (float x, float y), );
#  endif
_GL_CXXALIAS_SYS (hypotf, float, (float x, float y));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (hypotf);
# endif
#elif defined GNULIB_POSIXCHECK
# undef hypotf
# if HAVE_RAW_DECL_HYPOTF
_GL_WARN_ON_USE (hypotf, "hypotf is unportable - "
                 "use gnulib module hypotf for portability");
# endif
#endif

/* Return sqrt(x^2+y^2).  */
#if @GNULIB_HYPOT@
# if @REPLACE_HYPOT@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef hypot
#   define hypot rpl_hypot
#  endif
_GL_FUNCDECL_RPL (hypot, double, (double x, double y), );
_GL_CXXALIAS_RPL (hypot, double, (double x, double y));
# else
_GL_CXXALIAS_SYS (hypot, double, (double x, double y));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (hypot, double, (double x, double y));
# endif
#elif defined GNULIB_POSIXCHECK
# undef hypot
# if HAVE_RAW_DECL_HYPOT
_GL_WARN_ON_USE (hypotf, "hypot has portability problems - "
                 "use gnulib module hypot for portability");
# endif
#endif

/* Return sqrt(x^2+y^2).  */
#if @GNULIB_HYPOTL@
# if @REPLACE_HYPOTL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef hypotl
#   define hypotl rpl_hypotl
#  endif
_GL_FUNCDECL_RPL (hypotl, long double, (long double x, long double y), );
_GL_CXXALIAS_RPL (hypotl, long double, (long double x, long double y));
# else
#  if !@HAVE_HYPOTL@
_GL_FUNCDECL_SYS (hypotl, long double, (long double x, long double y), );
#  endif
_GL_CXXALIAS_SYS (hypotl, long double, (long double x, long double y));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (hypotl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef hypotl
# if HAVE_RAW_DECL_HYPOTL
_GL_WARN_ON_USE (hypotl, "hypotl is unportable - "
                 "use gnulib module hypotl for portability");
# endif
#endif


#if @GNULIB_ILOGBF@
# if @REPLACE_ILOGBF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef ilogbf
#   define ilogbf rpl_ilogbf
#  endif
_GL_FUNCDECL_RPL (ilogbf, int, (float x), );
_GL_CXXALIAS_RPL (ilogbf, int, (float x));
# else
#  if !@HAVE_ILOGBF@
_GL_FUNCDECL_SYS (ilogbf, int, (float x), );
#  endif
_GL_CXXALIAS_SYS (ilogbf, int, (float x));
# endif
_GL_CXXALIASWARN (ilogbf);
#elif defined GNULIB_POSIXCHECK
# undef ilogbf
# if HAVE_RAW_DECL_ILOGBF
_GL_WARN_ON_USE (ilogbf, "ilogbf is unportable - "
                 "use gnulib module ilogbf for portability");
# endif
#endif

#if @GNULIB_ILOGB@
# if @REPLACE_ILOGB@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef ilogb
#   define ilogb rpl_ilogb
#  endif
_GL_FUNCDECL_RPL (ilogb, int, (double x), );
_GL_CXXALIAS_RPL (ilogb, int, (double x));
# else
#  if !@HAVE_ILOGB@
_GL_FUNCDECL_SYS (ilogb, int, (double x), );
#  endif
_GL_CXXALIAS_SYS (ilogb, int, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (ilogb, int, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef ilogb
# if HAVE_RAW_DECL_ILOGB
_GL_WARN_ON_USE (ilogb, "ilogb is unportable - "
                 "use gnulib module ilogb for portability");
# endif
#endif

#if @GNULIB_ILOGBL@
# if @REPLACE_ILOGBL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef ilogbl
#   define ilogbl rpl_ilogbl
#  endif
_GL_FUNCDECL_RPL (ilogbl, int, (long double x), );
_GL_CXXALIAS_RPL (ilogbl, int, (long double x));
# else
#  if !@HAVE_ILOGBL@
#   undef ilogbl
_GL_FUNCDECL_SYS (ilogbl, int, (long double x), );
#  endif
_GL_CXXALIAS_SYS (ilogbl, int, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (ilogbl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef ilogbl
# if HAVE_RAW_DECL_ILOGBL
_GL_WARN_ON_USE (ilogbl, "ilogbl is unportable - "
                 "use gnulib module ilogbl for portability");
# endif
#endif


#if @GNULIB_MDA_J0@
/* On native Windows, map 'j0' to '_j0', so that -loldnames is not
   required.  In C++ with GNULIB_NAMESPACE, avoid differences between
   platforms by defining GNULIB_NAMESPACE::j0 always.  */
# if defined _WIN32 && !defined __CYGWIN__
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef j0
#   define j0 _j0
#  endif
_GL_CXXALIAS_MDA (j0, double, (double x));
# else
_GL_CXXALIAS_SYS (j0, double, (double x));
# endif
_GL_CXXALIASWARN (j0);
#endif

#if @GNULIB_MDA_J1@
/* On native Windows, map 'j1' to '_j1', so that -loldnames is not
   required.  In C++ with GNULIB_NAMESPACE, avoid differences between
   platforms by defining GNULIB_NAMESPACE::j1 always.  */
# if defined _WIN32 && !defined __CYGWIN__
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef j1
#   define j1 _j1
#  endif
_GL_CXXALIAS_MDA (j1, double, (double x));
# else
_GL_CXXALIAS_SYS (j1, double, (double x));
# endif
_GL_CXXALIASWARN (j1);
#endif

#if @GNULIB_MDA_JN@
/* On native Windows, map 'jn' to '_jn', so that -loldnames is not
   required.  In C++ with GNULIB_NAMESPACE, avoid differences between
   platforms by defining GNULIB_NAMESPACE::jn always.  */
# if defined _WIN32 && !defined __CYGWIN__
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef jn
#   define jn _jn
#  endif
_GL_CXXALIAS_MDA (jn, double, (int n, double x));
# else
_GL_CXXALIAS_SYS (jn, double, (int n, double x));
# endif
_GL_CXXALIASWARN (jn);
#endif


/* Return x * 2^exp.  */
#if @GNULIB_LDEXPF@
# if !@HAVE_LDEXPF@
#  undef ldexpf
_GL_FUNCDECL_SYS (ldexpf, float, (float x, int exp), );
# endif
_GL_CXXALIAS_SYS (ldexpf, float, (float x, int exp));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (ldexpf);
# endif
#elif defined GNULIB_POSIXCHECK
# undef ldexpf
# if HAVE_RAW_DECL_LDEXPF
_GL_WARN_ON_USE (ldexpf, "ldexpf is unportable - "
                 "use gnulib module ldexpf for portability");
# endif
#endif

/* Return x * 2^exp.  */
#if @GNULIB_LDEXP@
# if @REPLACE_LDEXP@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef ldexp
#   define ldexp rpl_ldexp
#  endif
_GL_FUNCDECL_RPL (ldexp, double, (double x, int exp), );
_GL_CXXALIAS_RPL (ldexp, double, (double x, int exp));
# else
/* Assume ldexp is always declared.  */
_GL_CXXALIAS_SYS (ldexp, double, (double x, int exp));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (ldexp, double, (double x, int exp));
# endif
#elif defined GNULIB_POSIXCHECK
# undef ldexp
/* Assume ldexp is always declared.  */
_GL_WARN_ON_USE (ldexp, "ldexp is unportable - "
                 "use gnulib module ldexp for portability");
#endif

/* Return x * 2^exp.  */
#if @GNULIB_LDEXPL@ && @REPLACE_LDEXPL@
# if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#  undef ldexpl
#  define ldexpl rpl_ldexpl
# endif
_GL_FUNCDECL_RPL (ldexpl, long double, (long double x, int exp), );
_GL_CXXALIAS_RPL (ldexpl, long double, (long double x, int exp));
#else
# if !@HAVE_DECL_LDEXPL@
_GL_FUNCDECL_SYS (ldexpl, long double, (long double x, int exp), );
# endif
# if @GNULIB_LDEXPL@
_GL_CXXALIAS_SYS (ldexpl, long double, (long double x, int exp));
# endif
#endif
#if @GNULIB_LDEXPL@
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (ldexpl);
# endif
#endif
#if !@GNULIB_LDEXPL@ && defined GNULIB_POSIXCHECK
# undef ldexpl
# if HAVE_RAW_DECL_LDEXPL
_GL_WARN_ON_USE (ldexpl, "ldexpl is unportable - "
                 "use gnulib module ldexpl for portability");
# endif
#endif


#if @GNULIB_LOGF@
# if @REPLACE_LOGF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef logf
#   define logf rpl_logf
#  endif
_GL_FUNCDECL_RPL (logf, float, (float x), );
_GL_CXXALIAS_RPL (logf, float, (float x));
# else
#  if !@HAVE_LOGF@
#   undef logf
_GL_FUNCDECL_SYS (logf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (logf, float, (float x));
# endif
_GL_CXXALIASWARN (logf);
#elif defined GNULIB_POSIXCHECK
# undef logf
# if HAVE_RAW_DECL_LOGF
_GL_WARN_ON_USE (logf, "logf is unportable - "
                 "use gnulib module logf for portability");
# endif
#endif

#if @GNULIB_LOG@
# if @REPLACE_LOG@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef log
#   define log rpl_log
#  endif
_GL_FUNCDECL_RPL (log, double, (double x), );
_GL_CXXALIAS_RPL (log, double, (double x));
# else
_GL_CXXALIAS_SYS (log, double, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (log, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef log
# if HAVE_RAW_DECL_LOG
_GL_WARN_ON_USE (log, "log has portability problems - "
                 "use gnulib module log for portability");
# endif
#endif

#if @GNULIB_LOGL@
# if @REPLACE_LOGL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef logl
#   define logl rpl_logl
#  endif
_GL_FUNCDECL_RPL (logl, long double, (long double x), );
_GL_CXXALIAS_RPL (logl, long double, (long double x));
# else
#  if !@HAVE_LOGL@ || !@HAVE_DECL_LOGL@
#   undef logl
_GL_FUNCDECL_SYS (logl, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (logl, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (logl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef logl
# if HAVE_RAW_DECL_LOGL
_GL_WARN_ON_USE (logl, "logl is unportable - "
                 "use gnulib module logl for portability");
# endif
#endif


#if @GNULIB_LOG10F@
# if @REPLACE_LOG10F@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef log10f
#   define log10f rpl_log10f
#  endif
_GL_FUNCDECL_RPL (log10f, float, (float x), );
_GL_CXXALIAS_RPL (log10f, float, (float x));
# else
#  if !@HAVE_LOG10F@
#   undef log10f
_GL_FUNCDECL_SYS (log10f, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (log10f, float, (float x));
# endif
_GL_CXXALIASWARN (log10f);
#elif defined GNULIB_POSIXCHECK
# undef log10f
# if HAVE_RAW_DECL_LOG10F
_GL_WARN_ON_USE (log10f, "log10f is unportable - "
                 "use gnulib module log10f for portability");
# endif
#endif

#if @GNULIB_LOG10@
# if @REPLACE_LOG10@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef log10
#   define log10 rpl_log10
#  endif
_GL_FUNCDECL_RPL (log10, double, (double x), );
_GL_CXXALIAS_RPL (log10, double, (double x));
# else
_GL_CXXALIAS_SYS (log10, double, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (log10, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef log10
# if HAVE_RAW_DECL_LOG10
_GL_WARN_ON_USE (log10, "log10 has portability problems - "
                 "use gnulib module log10 for portability");
# endif
#endif

#if @GNULIB_LOG10L@
# if @REPLACE_LOG10L@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef log10l
#   define log10l rpl_log10l
#  endif
_GL_FUNCDECL_RPL (log10l, long double, (long double x), );
_GL_CXXALIAS_RPL (log10l, long double, (long double x));
# else
#  if !@HAVE_LOG10L@ || !@HAVE_DECL_LOG10L@
#   undef log10l
_GL_FUNCDECL_SYS (log10l, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (log10l, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (log10l);
# endif
#elif defined GNULIB_POSIXCHECK
# undef log10l
# if HAVE_RAW_DECL_LOG10L
_GL_WARN_ON_USE (log10l, "log10l is unportable - "
                 "use gnulib module log10l for portability");
# endif
#endif


#if @GNULIB_LOG1PF@
# if @REPLACE_LOG1PF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef log1pf
#   define log1pf rpl_log1pf
#  endif
_GL_FUNCDECL_RPL (log1pf, float, (float x), );
_GL_CXXALIAS_RPL (log1pf, float, (float x));
# else
#  if !@HAVE_LOG1PF@
_GL_FUNCDECL_SYS (log1pf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (log1pf, float, (float x));
# endif
_GL_CXXALIASWARN (log1pf);
#elif defined GNULIB_POSIXCHECK
# undef log1pf
# if HAVE_RAW_DECL_LOG1PF
_GL_WARN_ON_USE (log1pf, "log1pf is unportable - "
                 "use gnulib module log1pf for portability");
# endif
#endif

#if @GNULIB_LOG1P@
# if @REPLACE_LOG1P@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef log1p
#   define log1p rpl_log1p
#  endif
_GL_FUNCDECL_RPL (log1p, double, (double x), );
_GL_CXXALIAS_RPL (log1p, double, (double x));
# else
#  if !@HAVE_LOG1P@
_GL_FUNCDECL_SYS (log1p, double, (double x), );
#  endif
_GL_CXXALIAS_SYS (log1p, double, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (log1p, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef log1p
# if HAVE_RAW_DECL_LOG1P
_GL_WARN_ON_USE (log1p, "log1p has portability problems - "
                 "use gnulib module log1p for portability");
# endif
#endif

#if @GNULIB_LOG1PL@
# if @REPLACE_LOG1PL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef log1pl
#   define log1pl rpl_log1pl
#  endif
_GL_FUNCDECL_RPL (log1pl, long double, (long double x), );
_GL_CXXALIAS_RPL (log1pl, long double, (long double x));
# else
#  if !@HAVE_LOG1PL@
_GL_FUNCDECL_SYS (log1pl, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (log1pl, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (log1pl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef log1pl
# if HAVE_RAW_DECL_LOG1PL
_GL_WARN_ON_USE (log1pl, "log1pl has portability problems - "
                 "use gnulib module log1pl for portability");
# endif
#endif


#if @GNULIB_LOG2F@
# if @REPLACE_LOG2F@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef log2f
#   define log2f rpl_log2f
#  endif
_GL_FUNCDECL_RPL (log2f, float, (float x), );
_GL_CXXALIAS_RPL (log2f, float, (float x));
# else
#  if !@HAVE_DECL_LOG2F@
#   undef log2f
_GL_FUNCDECL_SYS (log2f, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (log2f, float, (float x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (log2f);
# endif
#elif defined GNULIB_POSIXCHECK
# undef log2f
# if HAVE_RAW_DECL_LOG2F
_GL_WARN_ON_USE (log2f, "log2f is unportable - "
                 "use gnulib module log2f for portability");
# endif
#endif

#if @GNULIB_LOG2@
# if @REPLACE_LOG2@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef log2
#   define log2 rpl_log2
#  endif
_GL_FUNCDECL_RPL (log2, double, (double x), );
_GL_CXXALIAS_RPL (log2, double, (double x));
# else
#  if !@HAVE_DECL_LOG2@
#   undef log2
_GL_FUNCDECL_SYS (log2, double, (double x), );
#  endif
_GL_CXXALIAS_SYS (log2, double, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (log2, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef log2
# if HAVE_RAW_DECL_LOG2
_GL_WARN_ON_USE (log2, "log2 is unportable - "
                 "use gnulib module log2 for portability");
# endif
#endif

#if @GNULIB_LOG2L@
# if @REPLACE_LOG2L@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef log2l
#   define log2l rpl_log2l
#  endif
_GL_FUNCDECL_RPL (log2l, long double, (long double x), );
_GL_CXXALIAS_RPL (log2l, long double, (long double x));
# else
#  if !@HAVE_DECL_LOG2L@
_GL_FUNCDECL_SYS (log2l, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (log2l, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (log2l);
# endif
#elif defined GNULIB_POSIXCHECK
# undef log2l
# if HAVE_RAW_DECL_LOG2L
_GL_WARN_ON_USE (log2l, "log2l is unportable - "
                 "use gnulib module log2l for portability");
# endif
#endif


#if @GNULIB_LOGBF@
# if @REPLACE_LOGBF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef logbf
#   define logbf rpl_logbf
#  endif
_GL_FUNCDECL_RPL (logbf, float, (float x), );
_GL_CXXALIAS_RPL (logbf, float, (float x));
# else
#  if !@HAVE_LOGBF@
_GL_FUNCDECL_SYS (logbf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (logbf, float, (float x));
# endif
_GL_CXXALIASWARN (logbf);
#elif defined GNULIB_POSIXCHECK
# undef logbf
# if HAVE_RAW_DECL_LOGBF
_GL_WARN_ON_USE (logbf, "logbf is unportable - "
                 "use gnulib module logbf for portability");
# endif
#endif

#if @GNULIB_LOGB@
# if @REPLACE_LOGB@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef logb
#   define logb rpl_logb
#  endif
_GL_FUNCDECL_RPL (logb, double, (double x), );
_GL_CXXALIAS_RPL (logb, double, (double x));
# else
#  if !@HAVE_DECL_LOGB@
_GL_FUNCDECL_SYS (logb, double, (double x), );
#  endif
_GL_CXXALIAS_SYS (logb, double, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (logb, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef logb
# if HAVE_RAW_DECL_LOGB
_GL_WARN_ON_USE (logb, "logb is unportable - "
                 "use gnulib module logb for portability");
# endif
#endif

#if @GNULIB_LOGBL@
# if @REPLACE_LOGBL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef logbl
#   define logbl rpl_logbl
#  endif
_GL_FUNCDECL_RPL (logbl, long double, (long double x), );
_GL_CXXALIAS_RPL (logbl, long double, (long double x));
# else
#  if !@HAVE_LOGBL@
_GL_FUNCDECL_SYS (logbl, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (logbl, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (logbl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef logbl
# if HAVE_RAW_DECL_LOGBL
_GL_WARN_ON_USE (logbl, "logbl is unportable - "
                 "use gnulib module logbl for portability");
# endif
#endif


#if @GNULIB_LOGP1F@
# if !@HAVE_LOGP1F@
_GL_FUNCDECL_SYS (logp1f, float, (float x), );
# endif
_GL_CXXALIAS_SYS (logp1f, float, (float x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (logp1f, float, (float x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef logp1f
# if HAVE_RAW_DECL_LOGP1F
_GL_WARN_ON_USE (logp1f, "logp1f is unportable - "
                 "use gnulib module logp1f for portability");
# endif
#endif

#if @GNULIB_LOGP1@
# if !@HAVE_LOGP1@
_GL_FUNCDECL_SYS (logp1, double, (double x), );
# endif
_GL_CXXALIAS_SYS (logp1, double, (double x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (logp1, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef logp1
# if HAVE_RAW_DECL_LOGP1
_GL_WARN_ON_USE (logp1, "logp1 is unportable - "
                 "use gnulib module logp1 for portability");
# endif
#endif

#if @GNULIB_LOGP1L@
# if !@HAVE_LOGP1L@
_GL_FUNCDECL_SYS (logp1l, long double, (long double x), );
# endif
_GL_CXXALIAS_SYS (logp1l, long double, (long double x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (logp1l, long double, (long double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef logp1l
# if HAVE_RAW_DECL_LOGP1L
_GL_WARN_ON_USE (logp1l, "logp1l is unportable - "
                 "use gnulib module logp1l for portability");
# endif
#endif


#if @GNULIB_MODFF@
# if @REPLACE_MODFF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef modff
#   define modff rpl_modff
#  endif
_GL_FUNCDECL_RPL (modff, float, (float x, float *iptr), _GL_ARG_NONNULL ((2)));
_GL_CXXALIAS_RPL (modff, float, (float x, float *iptr));
# else
#  if !@HAVE_MODFF@
#   undef modff
_GL_FUNCDECL_SYS (modff, float, (float x, float *iptr), _GL_ARG_NONNULL ((2)));
#  endif
_GL_CXXALIAS_SYS (modff, float, (float x, float *iptr));
# endif
_GL_CXXALIASWARN (modff);
#elif defined GNULIB_POSIXCHECK
# undef modff
# if HAVE_RAW_DECL_MODFF
_GL_WARN_ON_USE (modff, "modff is unportable - "
                 "use gnulib module modff for portability");
# endif
#endif

#if @GNULIB_MODF@
# if @REPLACE_MODF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef modf
#   define modf rpl_modf
#  endif
_GL_FUNCDECL_RPL (modf, double, (double x, double *iptr),
                                _GL_ARG_NONNULL ((2)));
_GL_CXXALIAS_RPL (modf, double, (double x, double *iptr));
# else
_GL_CXXALIAS_SYS (modf, double, (double x, double *iptr));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (modf, double, (double x, double *iptr));
# endif
#elif defined GNULIB_POSIXCHECK
# undef modf
# if HAVE_RAW_DECL_MODF
_GL_WARN_ON_USE (modf, "modf has portability problems - "
                 "use gnulib module modf for portability");
# endif
#endif

#if @GNULIB_MODFL@
# if @REPLACE_MODFL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef modfl
#   define modfl rpl_modfl
#  endif
_GL_FUNCDECL_RPL (modfl, long double, (long double x, long double *iptr),
                                      _GL_ARG_NONNULL ((2)));
_GL_CXXALIAS_RPL (modfl, long double, (long double x, long double *iptr));
# else
#  if !@HAVE_MODFL@
#   undef modfl
_GL_FUNCDECL_SYS (modfl, long double, (long double x, long double *iptr),
                                      _GL_ARG_NONNULL ((2)));
#  endif
_GL_CXXALIAS_SYS (modfl, long double, (long double x, long double *iptr));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (modfl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef modfl
# if HAVE_RAW_DECL_MODFL
_GL_WARN_ON_USE (modfl, "modfl is unportable - "
                 "use gnulib module modfl for portability");
# endif
#endif


#if @GNULIB_POWF@
# if !@HAVE_POWF@
#  undef powf
_GL_FUNCDECL_SYS (powf, float, (float x, float y), );
# endif
_GL_CXXALIAS_SYS (powf, float, (float x, float y));
_GL_CXXALIASWARN (powf);
#elif defined GNULIB_POSIXCHECK
# undef powf
# if HAVE_RAW_DECL_POWF
_GL_WARN_ON_USE (powf, "powf is unportable - "
                 "use gnulib module powf for portability");
# endif
#endif


#if @GNULIB_REMAINDERF@
# if @REPLACE_REMAINDERF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef remainderf
#   define remainderf rpl_remainderf
#  endif
_GL_FUNCDECL_RPL (remainderf, float, (float x, float y), );
_GL_CXXALIAS_RPL (remainderf, float, (float x, float y));
# else
#  if !@HAVE_REMAINDERF@
_GL_FUNCDECL_SYS (remainderf, float, (float x, float y), );
#  endif
_GL_CXXALIAS_SYS (remainderf, float, (float x, float y));
# endif
_GL_CXXALIASWARN (remainderf);
#elif defined GNULIB_POSIXCHECK
# undef remainderf
# if HAVE_RAW_DECL_REMAINDERF
_GL_WARN_ON_USE (remainderf, "remainderf is unportable - "
                 "use gnulib module remainderf for portability");
# endif
#endif

#if @GNULIB_REMAINDER@
# if @REPLACE_REMAINDER@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef remainder
#   define remainder rpl_remainder
#  endif
_GL_FUNCDECL_RPL (remainder, double, (double x, double y), );
_GL_CXXALIAS_RPL (remainder, double, (double x, double y));
# else
#  if !@HAVE_REMAINDER@ || !@HAVE_DECL_REMAINDER@
_GL_FUNCDECL_SYS (remainder, double, (double x, double y), );
#  endif
_GL_CXXALIAS_SYS (remainder, double, (double x, double y));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (remainder, double, (double x, double y));
# endif
#elif defined GNULIB_POSIXCHECK
# undef remainder
# if HAVE_RAW_DECL_REMAINDER
_GL_WARN_ON_USE (remainder, "remainder is unportable - "
                 "use gnulib module remainder for portability");
# endif
#endif

#if @GNULIB_REMAINDERL@
# if @REPLACE_REMAINDERL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef remainderl
#   define remainderl rpl_remainderl
#  endif
_GL_FUNCDECL_RPL (remainderl, long double, (long double x, long double y), );
_GL_CXXALIAS_RPL (remainderl, long double, (long double x, long double y));
# else
#  if !@HAVE_DECL_REMAINDERL@
#   undef remainderl
#   if !(defined __cplusplus && defined _AIX)
_GL_FUNCDECL_SYS (remainderl, long double, (long double x, long double y), );
#   endif
#  endif
_GL_CXXALIAS_SYS (remainderl, long double, (long double x, long double y));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (remainderl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef remainderl
# if HAVE_RAW_DECL_REMAINDERL
_GL_WARN_ON_USE (remainderl, "remainderl is unportable - "
                 "use gnulib module remainderl for portability");
# endif
#endif


#if @GNULIB_RINTF@
# if !@HAVE_DECL_RINTF@
_GL_FUNCDECL_SYS (rintf, float, (float x), );
# endif
_GL_CXXALIAS_SYS (rintf, float, (float x));
_GL_CXXALIASWARN (rintf);
#elif defined GNULIB_POSIXCHECK
# undef rintf
# if HAVE_RAW_DECL_RINTF
_GL_WARN_ON_USE (rintf, "rintf is unportable - "
                 "use gnulib module rintf for portability");
# endif
#endif

#if @GNULIB_RINT@
# if !@HAVE_RINT@
_GL_FUNCDECL_SYS (rint, double, (double x), );
# endif
_GL_CXXALIAS_SYS (rint, double, (double x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (rint, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef rint
# if HAVE_RAW_DECL_RINT
_GL_WARN_ON_USE (rint, "rint is unportable - "
                 "use gnulib module rint for portability");
# endif
#endif

#if @GNULIB_RINTL@
# if @REPLACE_RINTL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef rintl
#   define rintl rpl_rintl
#  endif
_GL_FUNCDECL_RPL (rintl, long double, (long double x), );
_GL_CXXALIAS_RPL (rintl, long double, (long double x));
# else
#  if !@HAVE_RINTL@
_GL_FUNCDECL_SYS (rintl, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (rintl, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (rintl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef rintl
# if HAVE_RAW_DECL_RINTL
_GL_WARN_ON_USE (rintl, "rintl is unportable - "
                 "use gnulib module rintl for portability");
# endif
#endif


#if @GNULIB_ROUNDF@
# if @REPLACE_ROUNDF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef roundf
#   define roundf rpl_roundf
#  endif
_GL_FUNCDECL_RPL (roundf, float, (float x), );
_GL_CXXALIAS_RPL (roundf, float, (float x));
# else
#  if !@HAVE_DECL_ROUNDF@
_GL_FUNCDECL_SYS (roundf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (roundf, float, (float x));
# endif
_GL_CXXALIASWARN (roundf);
#elif defined GNULIB_POSIXCHECK
# undef roundf
# if HAVE_RAW_DECL_ROUNDF
_GL_WARN_ON_USE (roundf, "roundf is unportable - "
                 "use gnulib module roundf for portability");
# endif
#endif

#if @GNULIB_ROUND@
# if @REPLACE_ROUND@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef round
#   define round rpl_round
#  endif
_GL_FUNCDECL_RPL (round, double, (double x), );
_GL_CXXALIAS_RPL (round, double, (double x));
# else
#  if !@HAVE_DECL_ROUND@
_GL_FUNCDECL_SYS (round, double, (double x), );
#  endif
_GL_CXXALIAS_SYS (round, double, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (round, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef round
# if HAVE_RAW_DECL_ROUND
_GL_WARN_ON_USE (round, "round is unportable - "
                 "use gnulib module round for portability");
# endif
#endif

#if @GNULIB_ROUNDL@
# if @REPLACE_ROUNDL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef roundl
#   define roundl rpl_roundl
#  endif
_GL_FUNCDECL_RPL (roundl, long double, (long double x), );
_GL_CXXALIAS_RPL (roundl, long double, (long double x));
# else
#  if !@HAVE_DECL_ROUNDL@
#   undef roundl
#   if !(defined __cplusplus && defined _AIX)
_GL_FUNCDECL_SYS (roundl, long double, (long double x), );
#   endif
#  endif
_GL_CXXALIAS_SYS (roundl, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (roundl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef roundl
# if HAVE_RAW_DECL_ROUNDL
_GL_WARN_ON_USE (roundl, "roundl is unportable - "
                 "use gnulib module roundl for portability");
# endif
#endif


#if @GNULIB_SINF@
# if @REPLACE_SINF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef sinf
#   define sinf rpl_sinf
#  endif
_GL_FUNCDECL_RPL (sinf, float, (float x), );
_GL_CXXALIAS_RPL (sinf, float, (float x));
# else
#  if !@HAVE_SINF@
#   undef sinf
_GL_FUNCDECL_SYS (sinf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (sinf, float, (float x));
# endif
_GL_CXXALIASWARN (sinf);
#elif defined GNULIB_POSIXCHECK
# undef sinf
# if HAVE_RAW_DECL_SINF
_GL_WARN_ON_USE (sinf, "sinf is unportable - "
                 "use gnulib module sinf for portability");
# endif
#endif

#if @GNULIB_SINL@
# if !@HAVE_SINL@ || !@HAVE_DECL_SINL@
#  undef sinl
_GL_FUNCDECL_SYS (sinl, long double, (long double x), );
# endif
_GL_CXXALIAS_SYS (sinl, long double, (long double x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (sinl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef sinl
# if HAVE_RAW_DECL_SINL
_GL_WARN_ON_USE (sinl, "sinl is unportable - "
                 "use gnulib module sinl for portability");
# endif
#endif


#if @GNULIB_SINHF@
# if @REPLACE_SINHF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef sinhf
#   define sinhf rpl_sinhf
#  endif
_GL_FUNCDECL_RPL (sinhf, float, (float x), );
_GL_CXXALIAS_RPL (sinhf, float, (float x));
# else
#  if !@HAVE_SINHF@
#   undef sinhf
_GL_FUNCDECL_SYS (sinhf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (sinhf, float, (float x));
# endif
_GL_CXXALIASWARN (sinhf);
#elif defined GNULIB_POSIXCHECK
# undef sinhf
# if HAVE_RAW_DECL_SINHF
_GL_WARN_ON_USE (sinhf, "sinhf is unportable - "
                 "use gnulib module sinhf for portability");
# endif
#endif


#if @GNULIB_SQRTF@
# if @REPLACE_SQRTF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef sqrtf
#   define sqrtf rpl_sqrtf
#  endif
_GL_FUNCDECL_RPL (sqrtf, float, (float x), );
_GL_CXXALIAS_RPL (sqrtf, float, (float x));
# else
#  if !@HAVE_SQRTF@
#   undef sqrtf
_GL_FUNCDECL_SYS (sqrtf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (sqrtf, float, (float x));
# endif
_GL_CXXALIASWARN (sqrtf);
#elif defined GNULIB_POSIXCHECK
# undef sqrtf
# if HAVE_RAW_DECL_SQRTF
_GL_WARN_ON_USE (sqrtf, "sqrtf is unportable - "
                 "use gnulib module sqrtf for portability");
# endif
#endif

#if @GNULIB_SQRTL@
# if @REPLACE_SQRTL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef sqrtl
#   define sqrtl rpl_sqrtl
#  endif
_GL_FUNCDECL_RPL (sqrtl, long double, (long double x), );
_GL_CXXALIAS_RPL (sqrtl, long double, (long double x));
# else
#  if !@HAVE_SQRTL@ || !@HAVE_DECL_SQRTL@
#   undef sqrtl
_GL_FUNCDECL_SYS (sqrtl, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (sqrtl, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (sqrtl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef sqrtl
# if HAVE_RAW_DECL_SQRTL
_GL_WARN_ON_USE (sqrtl, "sqrtl is unportable - "
                 "use gnulib module sqrtl for portability");
# endif
#endif


#if @GNULIB_TANF@
# if @REPLACE_TANF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef tanf
#   define tanf rpl_tanf
#  endif
_GL_FUNCDECL_RPL (tanf, float, (float x), );
_GL_CXXALIAS_RPL (tanf, float, (float x));
# else
#  if !@HAVE_TANF@
#   undef tanf
_GL_FUNCDECL_SYS (tanf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (tanf, float, (float x));
# endif
_GL_CXXALIASWARN (tanf);
#elif defined GNULIB_POSIXCHECK
# undef tanf
# if HAVE_RAW_DECL_TANF
_GL_WARN_ON_USE (tanf, "tanf is unportable - "
                 "use gnulib module tanf for portability");
# endif
#endif

#if @GNULIB_TANL@
# if !@HAVE_TANL@ || !@HAVE_DECL_TANL@
#  undef tanl
_GL_FUNCDECL_SYS (tanl, long double, (long double x), );
# endif
_GL_CXXALIAS_SYS (tanl, long double, (long double x));
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (tanl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef tanl
# if HAVE_RAW_DECL_TANL
_GL_WARN_ON_USE (tanl, "tanl is unportable - "
                 "use gnulib module tanl for portability");
# endif
#endif


#if @GNULIB_TANHF@
# if @REPLACE_TANHF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef tanhf
#   define tanhf rpl_tanhf
#  endif
_GL_FUNCDECL_RPL (tanhf, float, (float x), );
_GL_CXXALIAS_RPL (tanhf, float, (float x));
# else
#  if !@HAVE_TANHF@
#   undef tanhf
_GL_FUNCDECL_SYS (tanhf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (tanhf, float, (float x));
# endif
_GL_CXXALIASWARN (tanhf);
#elif defined GNULIB_POSIXCHECK
# undef tanhf
# if HAVE_RAW_DECL_TANHF
_GL_WARN_ON_USE (tanhf, "tanhf is unportable - "
                 "use gnulib module tanhf for portability");
# endif
#endif


#if @GNULIB_TRUNCF@
# if @REPLACE_TRUNCF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef truncf
#   define truncf rpl_truncf
#  endif
_GL_FUNCDECL_RPL (truncf, float, (float x), );
_GL_CXXALIAS_RPL (truncf, float, (float x));
# else
#  if !@HAVE_DECL_TRUNCF@
_GL_FUNCDECL_SYS (truncf, float, (float x), );
#  endif
_GL_CXXALIAS_SYS (truncf, float, (float x));
# endif
_GL_CXXALIASWARN (truncf);
#elif defined GNULIB_POSIXCHECK
# undef truncf
# if HAVE_RAW_DECL_TRUNCF
_GL_WARN_ON_USE (truncf, "truncf is unportable - "
                 "use gnulib module truncf for portability");
# endif
#endif

#if @GNULIB_TRUNC@
# if @REPLACE_TRUNC@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef trunc
#   define trunc rpl_trunc
#  endif
_GL_FUNCDECL_RPL (trunc, double, (double x), );
_GL_CXXALIAS_RPL (trunc, double, (double x));
# else
#  if !@HAVE_DECL_TRUNC@
_GL_FUNCDECL_SYS (trunc, double, (double x), );
#  endif
_GL_CXXALIAS_SYS (trunc, double, (double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (trunc, double, (double x));
# endif
#elif defined GNULIB_POSIXCHECK
# undef trunc
# if HAVE_RAW_DECL_TRUNC
_GL_WARN_ON_USE (trunc, "trunc is unportable - "
                 "use gnulib module trunc for portability");
# endif
#endif

#if @GNULIB_TRUNCL@
# if @REPLACE_TRUNCL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef truncl
#   define truncl rpl_truncl
#  endif
_GL_FUNCDECL_RPL (truncl, long double, (long double x), );
_GL_CXXALIAS_RPL (truncl, long double, (long double x));
# else
#  if !@HAVE_DECL_TRUNCL@
_GL_FUNCDECL_SYS (truncl, long double, (long double x), );
#  endif
_GL_CXXALIAS_SYS (truncl, long double, (long double x));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN (truncl);
# endif
#elif defined GNULIB_POSIXCHECK
# undef truncl
# if HAVE_RAW_DECL_TRUNCL
_GL_WARN_ON_USE (truncl, "truncl is unportable - "
                 "use gnulib module truncl for portability");
# endif
#endif


#if @GNULIB_MDA_Y0@
/* On native Windows, map 'y0' to '_y0', so that -loldnames is not
   required.  In C++ with GNULIB_NAMESPACE, avoid differences between
   platforms by defining GNULIB_NAMESPACE::y0 always.  */
# if defined _WIN32 && !defined __CYGWIN__
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef y0
#   define y0 _y0
#  endif
_GL_CXXALIAS_MDA (y0, double, (double x));
# else
_GL_CXXALIAS_SYS (y0, double, (double x));
# endif
_GL_CXXALIASWARN (y0);
#endif

#if @GNULIB_MDA_Y1@
/* On native Windows, map 'y1' to '_y1', so that -loldnames is not
   required.  In C++ with GNULIB_NAMESPACE, avoid differences between
   platforms by defining GNULIB_NAMESPACE::y1 always.  */
# if defined _WIN32 && !defined __CYGWIN__
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef y1
#   define y1 _y1
#  endif
_GL_CXXALIAS_MDA (y1, double, (double x));
# else
_GL_CXXALIAS_SYS (y1, double, (double x));
# endif
_GL_CXXALIASWARN (y1);
#endif

#if @GNULIB_MDA_YN@
/* On native Windows, map 'yn' to '_yn', so that -loldnames is not
   required.  In C++ with GNULIB_NAMESPACE, avoid differences between
   platforms by defining GNULIB_NAMESPACE::yn always.  */
# if defined _WIN32 && !defined __CYGWIN__
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef yn
#   define yn _yn
#  endif
_GL_CXXALIAS_MDA (yn, double, (int n, double x));
# else
_GL_CXXALIAS_SYS (yn, double, (int n, double x));
# endif
_GL_CXXALIASWARN (yn);
#endif


/* Definitions of function-like macros come here, after the function
   declarations.  */


#if @GNULIB_ISFINITE@
# if @REPLACE_ISFINITE@
_GL_EXTERN_C int gl_isfinitef (float x);
_GL_EXTERN_C int gl_isfinited (double x);
_GL_EXTERN_C int gl_isfinitel (long double x);
#  undef isfinite
#  define isfinite(x) \
   (sizeof (x) == sizeof (long double) ? gl_isfinitel (x) : \
    sizeof (x) == sizeof (double) ? gl_isfinited (x) : \
    gl_isfinitef (x))
# endif
# ifdef __cplusplus
#  if defined isfinite || defined GNULIB_NAMESPACE
_GL_MATH_CXX_REAL_FLOATING_DECL_1 (isfinite)
#   undef isfinite
#   if __GNUC__ >= 6 || (defined __clang__ && !((defined __APPLE__ && defined __MACH__) || defined __FreeBSD__ || defined __OpenBSD__ || defined _AIX || (defined _WIN32 && !defined __CYGWIN__)))
  /* This platform's <cmath> possibly defines isfinite through a set of inline
     functions.  */
_GL_MATH_CXX_REAL_FLOATING_DECL_2 (isfinite, rpl_isfinite, bool)
#    define isfinite rpl_isfinite
#    define GNULIB_NAMESPACE_LACKS_ISFINITE 1
#   else
_GL_MATH_CXX_REAL_FLOATING_DECL_2 (isfinite, isfinite, bool)
#   endif
#  endif
# endif
#elif defined GNULIB_POSIXCHECK
# if defined isfinite
_GL_WARN_REAL_FLOATING_DECL (isfinite);
#  undef isfinite
#  define isfinite(x) _GL_WARN_REAL_FLOATING_IMPL (isfinite, x)
# endif
#endif


#if @GNULIB_ISINF@
# if @REPLACE_ISINF@
_GL_EXTERN_C int gl_isinff (float x);
_GL_EXTERN_C int gl_isinfd (double x);
_GL_EXTERN_C int gl_isinfl (long double x);
#  undef isinf
#  define isinf(x) \
   (sizeof (x) == sizeof (long double) ? gl_isinfl (x) : \
    sizeof (x) == sizeof (double) ? gl_isinfd (x) : \
    gl_isinff (x))
# endif
# ifdef __cplusplus
#  if defined isinf || defined GNULIB_NAMESPACE
_GL_MATH_CXX_REAL_FLOATING_DECL_1 (isinf)
#   undef isinf
#   if __GNUC__ >= 6 || (defined __clang__ && !((defined __APPLE__ && defined __MACH__) || defined __FreeBSD__ || defined __OpenBSD__ || (defined _WIN32 && !defined __CYGWIN__)))
  /* This platform's <cmath> possibly defines isinf through a set of inline
     functions.  */
_GL_MATH_CXX_REAL_FLOATING_DECL_2 (isinf, rpl_isinf, bool)
#    define isinf rpl_isinf
#    define GNULIB_NAMESPACE_LACKS_ISINF 1
#   else
_GL_MATH_CXX_REAL_FLOATING_DECL_2 (isinf, isinf, bool)
#   endif
#  endif
# endif
#elif defined GNULIB_POSIXCHECK
# if defined isinf
_GL_WARN_REAL_FLOATING_DECL (isinf);
#  undef isinf
#  define isinf(x) _GL_WARN_REAL_FLOATING_IMPL (isinf, x)
# endif
#endif


#if @GNULIB_ISNANF@
/* Test for NaN for 'float' numbers.  */
# if @HAVE_ISNANF@
#  if defined __sun || defined __sgi
/* Solaris and IRIX have isnanf() and declare it in <ieeefp.h>.  We cannot
   define isnanf as a macro, because that would conflict with <ieeefp.h>.  */
_GL_EXTERN_C int isnanf (float x);
#  else
/* The original <math.h> included above provides a declaration of isnan macro
   or (older) isnanf function.  */
#   if (__GNUC__ >= 4) || (__clang_major__ >= 4)
    /* GCC >= 4.0 and clang provide a type-generic built-in for isnan.
       GCC >= 4.0 also provides __builtin_isnanf, but clang doesn't.  */
#    undef isnanf
#    define isnanf(x) __builtin_isnan ((float)(x))
#   elif defined isnan && !defined HAVE_ISNANF_NOLIBM
#    undef isnanf
#    define isnanf(x) isnan ((float)(x))
#   endif
#  endif
# else
/* Test whether X is a NaN.  */
#  undef isnanf
#  define isnanf rpl_isnanf
_GL_EXTERN_C int isnanf (float x);
# endif
#endif

#if @GNULIB_ISNAND@
/* Test for NaN for 'double' numbers.
   This function is a gnulib extension, unlike isnan() which applied only
   to 'double' numbers earlier but now is a type-generic macro.  */
# if @HAVE_ISNAND@
#  if defined __sun || defined __sgi
/* Solaris and IRIX have isnand() and declare it in <ieeefp.h>.  We cannot
   define isnand as a macro, because that would conflict with <ieeefp.h>.  */
_GL_EXTERN_C int isnand (double x);
#  else
/* The original <math.h> included above provides a declaration of isnan
   macro.  */
#   if (__GNUC__ >= 4) || (__clang_major__ >= 4)
    /* GCC >= 4.0 and clang provide a type-generic built-in for isnan.  */
#    undef isnand
#    define isnand(x) __builtin_isnan ((double)(x))
#   elif !defined HAVE_ISNAND_NOLIBM
#    undef isnand
#    define isnand(x) isnan ((double)(x))
#   endif
#  endif
# else
/* Test whether X is a NaN.  */
#  undef isnand
#  define isnand rpl_isnand
_GL_EXTERN_C int isnand (double x);
# endif
#endif

#if @GNULIB_ISNANL@
/* Test for NaN for 'long double' numbers.  */
# if @HAVE_ISNANL@
/* The original <math.h> included above provides a declaration of isnan
   macro or (older) isnanl function.  */
#  if (__GNUC__ >= 4) || (__clang_major__ >= 4)
    /* GCC >= 4.0 and clang provide a type-generic built-in for isnan.
       GCC >= 4.0 also provides __builtin_isnanl, but clang doesn't.  */
#   undef isnanl
#   define isnanl(x) __builtin_isnan ((long double)(x))
#  elif defined isnan && !defined HAVE_ISNANL_NOLIBM
#   undef isnanl
#   define isnanl(x) isnan ((long double)(x))
#  endif
# else
/* Test whether X is a NaN.  */
#  undef isnanl
#  define isnanl rpl_isnanl
_GL_EXTERN_C int isnanl (long double x) _GL_ATTRIBUTE_CONST;
# endif
#endif

/* This must come *after* the snippets for GNULIB_ISNANF and GNULIB_ISNANL!  */
#if @GNULIB_ISNAN@
# if @REPLACE_ISNAN@
/* We can't just use the isnanf macro (e.g.) as exposed by
   isnanf.h (e.g.) here, because those may end up being macros
   that recursively expand back to isnan.  So use the gnulib
   replacements for them directly. */
#  if @HAVE_ISNANF@ && (__GNUC__ >= 4) || (__clang_major__ >= 4)
#   define gl_isnan_f(x) __builtin_isnan ((float)(x))
#  else
_GL_EXTERN_C int rpl_isnanf (float x);
#   define gl_isnan_f(x) rpl_isnanf (x)
#  endif
#  if @HAVE_ISNAND@ && (__GNUC__ >= 4) || (__clang_major__ >= 4)
#   define gl_isnan_d(x) __builtin_isnan ((double)(x))
#  else
_GL_EXTERN_C int rpl_isnand (double x);
#   define gl_isnan_d(x) rpl_isnand (x)
#  endif
#  if @HAVE_ISNANL@ && (__GNUC__ >= 4) || (__clang_major__ >= 4)
#   define gl_isnan_l(x) __builtin_isnan ((long double)(x))
#  else
_GL_EXTERN_C int rpl_isnanl (long double x) _GL_ATTRIBUTE_CONST;
#   define gl_isnan_l(x) rpl_isnanl (x)
#  endif
#  undef isnan
#  define isnan(x) \
   (sizeof (x) == sizeof (long double) ? gl_isnan_l (x) : \
    sizeof (x) == sizeof (double) ? gl_isnan_d (x) : \
    gl_isnan_f (x))
# elif (__GNUC__ >= 4) || (__clang_major__ >= 4)
#  undef isnan
#  define isnan(x) \
   (sizeof (x) == sizeof (long double) ? __builtin_isnan ((long double)(x)) : \
    sizeof (x) == sizeof (double) ? __builtin_isnan ((double)(x)) : \
    __builtin_isnan ((float)(x)))
# endif
# ifdef __cplusplus
#  if defined isnan || defined GNULIB_NAMESPACE
_GL_MATH_CXX_REAL_FLOATING_DECL_1 (isnan)
#   undef isnan
#   if __GNUC__ >= 6 || (defined __clang__ && !((defined __APPLE__ && defined __MACH__ && __clang_major__ != 12) || (defined __FreeBSD__ && (__clang_major__ < 7 || __clang_major__ >= 11)) || defined __OpenBSD__ || (defined _WIN32 && !defined __CYGWIN__)))
  /* This platform's <cmath> possibly defines isnan through a set of inline
     functions.  */
_GL_MATH_CXX_REAL_FLOATING_DECL_2 (isnan, rpl_isnan, bool)
#    define isnan rpl_isnan
#    define GNULIB_NAMESPACE_LACKS_ISNAN 1
#   elif __clang_major__ >= 14
  /* Neither of the two possible _GL_MATH_CXX_REAL_FLOATING_DECL_2 invocations
     works.  Inline functions are already present in /usr/include/c++/v1/math.h,
     which comes from LLVM.  */
#    define GNULIB_NAMESPACE_LACKS_ISNAN 1
#   else
_GL_MATH_CXX_REAL_FLOATING_DECL_2 (isnan, isnan, bool)
#   endif
#  endif
# else
/* Ensure isnan is a macro.  */
#  ifndef isnan
#   define isnan isnan
#  endif
# endif
#elif defined GNULIB_POSIXCHECK
# if defined isnan
_GL_WARN_REAL_FLOATING_DECL (isnan);
#  undef isnan
#  define isnan(x) _GL_WARN_REAL_FLOATING_IMPL (isnan, x)
# endif
#endif


#if @GNULIB_SIGNBIT@
# if (@REPLACE_SIGNBIT_USING_BUILTINS@ \
      && (!defined __cplusplus || __cplusplus < 201103))
#  undef signbit
   /* GCC >= 4.0 and clang provide three built-ins for signbit.  */
#  define signbit(x) \
   (sizeof (x) == sizeof (long double) ? __builtin_signbitl (x) : \
    sizeof (x) == sizeof (double) ? __builtin_signbit (x) : \
    __builtin_signbitf (x))
# endif
# if @REPLACE_SIGNBIT@ && !GNULIB_defined_signbit
#  undef signbit
_GL_EXTERN_C int gl_signbitf (float arg);
_GL_EXTERN_C int gl_signbitd (double arg);
_GL_EXTERN_C int gl_signbitl (long double arg);
#  if __GNUC__ >= 2 || defined __clang__
#   define _GL_NUM_UINT_WORDS(type) \
      ((sizeof (type) + sizeof (unsigned int) - 1) / sizeof (unsigned int))
#   if defined FLT_SIGNBIT_WORD && defined FLT_SIGNBIT_BIT && !defined gl_signbitf
#    define gl_signbitf_OPTIMIZED_MACRO
#    define gl_signbitf(arg) \
       __extension__                                                    \
       ({ union { float _value;                                         \
                  unsigned int _word[_GL_NUM_UINT_WORDS (float)];       \
                } _m;                                                   \
          _m._value = (arg);                                            \
          (_m._word[FLT_SIGNBIT_WORD] >> FLT_SIGNBIT_BIT) & 1;          \
        })
#   endif
#   if defined DBL_SIGNBIT_WORD && defined DBL_SIGNBIT_BIT && !defined gl_signbitd
#    define gl_signbitd_OPTIMIZED_MACRO
#    define gl_signbitd(arg) \
       __extension__                                                    \
       ({ union { double _value;                                        \
                  unsigned int _word[_GL_NUM_UINT_WORDS (double)];      \
                } _m;                                                   \
          _m._value = (arg);                                            \
          (_m._word[DBL_SIGNBIT_WORD] >> DBL_SIGNBIT_BIT) & 1;          \
        })
#   endif
#   if defined LDBL_SIGNBIT_WORD && defined LDBL_SIGNBIT_BIT && !defined gl_signbitl
#    define gl_signbitl_OPTIMIZED_MACRO
#    define gl_signbitl(arg) \
       __extension__                                                    \
       ({ union { long double _value;                                   \
                  unsigned int _word[_GL_NUM_UINT_WORDS (long double)]; \
                } _m;                                                   \
          _m._value = (arg);                                            \
          (_m._word[LDBL_SIGNBIT_WORD] >> LDBL_SIGNBIT_BIT) & 1;        \
        })
#   endif
#  endif
#  define signbit(x) \
   (sizeof (x) == sizeof (long double) ? gl_signbitl (x) : \
    sizeof (x) == sizeof (double) ? gl_signbitd (x) : \
    gl_signbitf (x))
#  define GNULIB_defined_signbit 1
# endif
# ifdef __cplusplus
#  if defined signbit || defined GNULIB_NAMESPACE
_GL_MATH_CXX_REAL_FLOATING_DECL_1 (signbit)
#   undef signbit
#   if __cplusplus >= 201103L || __GNUC__ >= 6 || (defined __clang__ && !((defined __APPLE__ && defined __MACH__) || defined __FreeBSD__ || defined __OpenBSD__ || defined _AIX || (defined _WIN32 && !defined __CYGWIN__)))
  /* This platform's <cmath> possibly defines signbit through a set of inline
     functions.  */
_GL_MATH_CXX_REAL_FLOATING_DECL_2 (signbit, rpl_signbit, bool)
#    define signbit rpl_signbit
#    define GNULIB_NAMESPACE_LACKS_SIGNBIT 1
#   else
_GL_MATH_CXX_REAL_FLOATING_DECL_2 (signbit, signbit, bool)
#   endif
#  endif
# endif
#elif defined GNULIB_POSIXCHECK
# if defined signbit
_GL_WARN_REAL_FLOATING_DECL (signbit);
#  undef signbit
#  define signbit(x) _GL_WARN_REAL_FLOATING_IMPL (signbit, x)
# endif
#endif


#if @GNULIB_GETPAYLOADF@
# if @REPLACE_GETPAYLOADF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef getpayloadf
#   define getpayloadf rpl_getpayloadf
#  endif
_GL_FUNCDECL_RPL (getpayloadf, float, (const float *), );
_GL_CXXALIAS_RPL (getpayloadf, float, (const float *));
# else
#  if !@HAVE_GETPAYLOADF@
_GL_FUNCDECL_SYS (getpayloadf, float, (const float *), );
#  endif
_GL_CXXALIAS_SYS (getpayloadf, float, (const float *));
# endif
_GL_CXXALIASWARN (getpayloadf);
#elif defined GNULIB_POSIXCHECK
# undef getpayloadf
# if HAVE_RAW_DECL_GETPAYLOADF
_GL_WARN_ON_USE (getpayloadf, "getpayloadf is unportable - "
                 "use gnulib module getpayloadf for portability");
# endif
#endif

#if @GNULIB_GETPAYLOAD@
# if @REPLACE_GETPAYLOAD@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef getpayload
#   define getpayload rpl_getpayload
#  endif
_GL_FUNCDECL_RPL (getpayload, double, (const double *), );
_GL_CXXALIAS_RPL (getpayload, double, (const double *));
# else
#  if !@HAVE_GETPAYLOAD@
_GL_FUNCDECL_SYS (getpayload, double, (const double *), );
#  endif
_GL_CXXALIAS_SYS (getpayload, double, (const double *));
# endif
_GL_CXXALIASWARN (getpayload);
#elif defined GNULIB_POSIXCHECK
# undef getpayload
# if HAVE_RAW_DECL_GETPAYLOAD
_GL_WARN_ON_USE (getpayload, "getpayload is unportable - "
                 "use gnulib module getpayload for portability");
# endif
#endif

#if @GNULIB_GETPAYLOADL@
# if @REPLACE_GETPAYLOADL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef getpayloadl
#   define getpayloadl rpl_getpayloadl
#  endif
_GL_FUNCDECL_RPL (getpayloadl, long double, (const long double *), );
_GL_CXXALIAS_RPL (getpayloadl, long double, (const long double *));
# else
#  if !@HAVE_GETPAYLOADL@
_GL_FUNCDECL_SYS (getpayloadl, long double, (const long double *), );
#  endif
_GL_CXXALIAS_SYS (getpayloadl, long double, (const long double *));
# endif
_GL_CXXALIASWARN (getpayloadl);
#elif defined GNULIB_POSIXCHECK
# undef getpayloadl
# if HAVE_RAW_DECL_GETPAYLOADL
_GL_WARN_ON_USE (getpayloadl, "getpayloadl is unportable - "
                 "use gnulib module getpayloadl for portability");
# endif
#endif


#if @GNULIB_SETPAYLOADF@
# if !@HAVE_SETPAYLOADF@
_GL_FUNCDECL_SYS (setpayloadf, int, (float *, float), );
# endif
_GL_CXXALIAS_SYS (setpayloadf, int, (float *, float));
_GL_CXXALIASWARN (setpayloadf);
#elif defined GNULIB_POSIXCHECK
# undef setpayloadf
# if HAVE_RAW_DECL_SETPAYLOADF
_GL_WARN_ON_USE (setpayloadf, "setpayloadf is unportable - "
                 "use gnulib module setpayloadf for portability");
# endif
#endif

#if @GNULIB_SETPAYLOAD@
# if !@HAVE_SETPAYLOAD@
_GL_FUNCDECL_SYS (setpayload, int, (double *, double), );
# endif
_GL_CXXALIAS_SYS (setpayload, int, (double *, double));
_GL_CXXALIASWARN (setpayload);
#elif defined GNULIB_POSIXCHECK
# undef setpayload
# if HAVE_RAW_DECL_SETPAYLOAD
_GL_WARN_ON_USE (setpayload, "setpayload is unportable - "
                 "use gnulib module setpayload for portability");
# endif
#endif

#if @GNULIB_SETPAYLOADL@
# if !@HAVE_SETPAYLOADL@
_GL_FUNCDECL_SYS (setpayloadl, int, (long double *, long double), );
# endif
_GL_CXXALIAS_SYS (setpayloadl, int, (long double *, long double));
_GL_CXXALIASWARN (setpayloadl);
#elif defined GNULIB_POSIXCHECK
# undef setpayloadl
# if HAVE_RAW_DECL_SETPAYLOADL
_GL_WARN_ON_USE (setpayloadl, "setpayloadl is unportable - "
                 "use gnulib module setpayloadl for portability");
# endif
#endif


#if @GNULIB_SETPAYLOADSIGF@
# if !@HAVE_SETPAYLOADSIGF@
_GL_FUNCDECL_SYS (setpayloadsigf, int, (float *, float), );
# endif
_GL_CXXALIAS_SYS (setpayloadsigf, int, (float *, float));
_GL_CXXALIASWARN (setpayloadsigf);
#elif defined GNULIB_POSIXCHECK
# undef setpayloadsigf
# if HAVE_RAW_DECL_SETPAYLOADSIGF
_GL_WARN_ON_USE (setpayloadsigf, "setpayloadsigf is unportable - "
                 "use gnulib module setpayloadsigf for portability");
# endif
#endif

#if @GNULIB_SETPAYLOADSIG@
# if !@HAVE_SETPAYLOADSIG@
_GL_FUNCDECL_SYS (setpayloadsig, int, (double *, double), );
# endif
_GL_CXXALIAS_SYS (setpayloadsig, int, (double *, double));
_GL_CXXALIASWARN (setpayloadsig);
#elif defined GNULIB_POSIXCHECK
# undef setpayloadsig
# if HAVE_RAW_DECL_SETPAYLOADSIG
_GL_WARN_ON_USE (setpayloadsig, "setpayloadsig is unportable - "
                 "use gnulib module setpayloadsig for portability");
# endif
#endif

#if @GNULIB_SETPAYLOADSIGL@
# if !@HAVE_SETPAYLOADSIGL@
_GL_FUNCDECL_SYS (setpayloadsigl, int, (long double *, long double), );
# endif
_GL_CXXALIAS_SYS (setpayloadsigl, int, (long double *, long double));
_GL_CXXALIASWARN (setpayloadsigl);
#elif defined GNULIB_POSIXCHECK
# undef setpayloadsigl
# if HAVE_RAW_DECL_SETPAYLOADSIGL
_GL_WARN_ON_USE (setpayloadsigl, "setpayloadsigl is unportable - "
                 "use gnulib module setpayloadsigl for portability");
# endif
#endif


#if @GNULIB_TOTALORDERF@
# if @REPLACE_TOTALORDERF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef totalorderf
#   define totalorderf rpl_totalorderf
#  endif
_GL_FUNCDECL_RPL (totalorderf, int, (float const *, float const *), );
_GL_CXXALIAS_RPL (totalorderf, int, (float const *, float const *));
# else
#  if !@HAVE_TOTALORDERF@
_GL_FUNCDECL_SYS (totalorderf, int, (float const *, float const *), );
#  endif
_GL_CXXALIAS_SYS (totalorderf, int, (float const *, float const *));
# endif
_GL_CXXALIASWARN (totalorderf);
#elif defined GNULIB_POSIXCHECK
# undef totalorderf
# if HAVE_RAW_DECL_TOTALORDERF
_GL_WARN_ON_USE (totalorderf, "totalorderf is unportable - "
                 "use gnulib module totalorderf for portability");
# endif
#endif

#if @GNULIB_TOTALORDER@
# if @REPLACE_TOTALORDER@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef totalorder
#   define totalorder rpl_totalorder
#  endif
_GL_FUNCDECL_RPL (totalorder, int, (double const *, double const *), );
_GL_CXXALIAS_RPL (totalorder, int, (double const *, double const *));
# else
#  if !@HAVE_TOTALORDER@
_GL_FUNCDECL_SYS (totalorder, int, (double const *, double const *), );
#  endif
_GL_CXXALIAS_SYS (totalorder, int, (double const *, double const *));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (totalorder, int, (double const *, double const *));
# endif
#elif defined GNULIB_POSIXCHECK
# undef totalorder
# if HAVE_RAW_DECL_TOTALORDER
_GL_WARN_ON_USE (totalorder, "totalorder is unportable - "
                 "use gnulib module totalorder for portability");
# endif
#endif

#if @GNULIB_TOTALORDERL@
# if @REPLACE_TOTALORDERL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef totalorderl
#   define totalorderl rpl_totalorderl
#  endif
_GL_FUNCDECL_RPL (totalorderl, int,
                  (long double const *, long double const *), );
_GL_CXXALIAS_RPL (totalorderl, int,
                  (long double const *, long double const *));
# else
#  if !@HAVE_TOTALORDERL@
_GL_FUNCDECL_SYS (totalorderl, int,
                  (long double const *, long double const *), );
#  endif
_GL_CXXALIAS_SYS (totalorderl, int,
                  (long double const *, long double const *));
# endif
_GL_CXXALIASWARN (totalorderl);
#elif defined GNULIB_POSIXCHECK
# undef totalorderl
# if HAVE_RAW_DECL_TOTALORDERL
_GL_WARN_ON_USE (totalorderl, "totalorderl is unportable - "
                 "use gnulib module totalorderl for portability");
# endif
#endif


#if @GNULIB_TOTALORDERMAGF@
# if @REPLACE_TOTALORDERMAGF@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef totalordermagf
#   define totalordermagf rpl_totalordermagf
#  endif
_GL_FUNCDECL_RPL (totalordermagf, int, (float const *, float const *), );
_GL_CXXALIAS_RPL (totalordermagf, int, (float const *, float const *));
# else
#  if !@HAVE_TOTALORDERMAGF@
_GL_FUNCDECL_SYS (totalordermagf, int, (float const *, float const *), );
#  endif
_GL_CXXALIAS_SYS (totalordermagf, int, (float const *, float const *));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (totalordermagf, int, (float const *, float const *));
# endif
#elif defined GNULIB_POSIXCHECK
# undef totalordermagf
# if HAVE_RAW_DECL_TOTALORDERMAGF
_GL_WARN_ON_USE (totalordermagf, "totalordermagf is unportable - "
                 "use gnulib module totalordermagf for portability");
# endif
#endif

#if @GNULIB_TOTALORDERMAG@
# if @REPLACE_TOTALORDERMAG@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef totalordermag
#   define totalordermag rpl_totalordermag
#  endif
_GL_FUNCDECL_RPL (totalordermag, int, (double const *, double const *), );
_GL_CXXALIAS_RPL (totalordermag, int, (double const *, double const *));
# else
#  if !@HAVE_TOTALORDERMAG@
_GL_FUNCDECL_SYS (totalordermag, int, (double const *, double const *), );
#  endif
_GL_CXXALIAS_SYS (totalordermag, int, (double const *, double const *));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (totalordermag, int, (double const *, double const *));
# endif
#elif defined GNULIB_POSIXCHECK
# undef totalordermag
# if HAVE_RAW_DECL_TOTALORDERMAG
_GL_WARN_ON_USE (totalordermag, "totalordermag is unportable - "
                 "use gnulib module totalordermag for portability");
# endif
#endif

#if @GNULIB_TOTALORDERMAGL@
# if @REPLACE_TOTALORDERMAGL@
#  if !(defined __cplusplus && defined GNULIB_NAMESPACE)
#   undef totalordermagl
#   define totalordermagl rpl_totalordermagl
#  endif
_GL_FUNCDECL_RPL (totalordermagl, int,
                  (long double const *, long double const *), );
_GL_CXXALIAS_RPL (totalordermagl, int,
                  (long double const *, long double const *));
# else
#  if !@HAVE_TOTALORDERMAGL@
_GL_FUNCDECL_SYS (totalordermagl, int,
                  (long double const *, long double const *), );
#  endif
_GL_CXXALIAS_SYS (totalordermagl, int,
                  (long double const *, long double const *));
# endif
# if __GLIBC__ >= 2
_GL_CXXALIASWARN1 (totalordermagl, int,
                   (long double const *, long double const *));
# endif
#elif defined GNULIB_POSIXCHECK
# undef totalordermagl
# if HAVE_RAW_DECL_TOTALORDERMAGL
_GL_WARN_ON_USE (totalordermagl, "totalordermagl is unportable - "
                 "use gnulib module totalordermagl for portability");
# endif
#endif


_GL_INLINE_HEADER_END

#endif /* _@GUARD_PREFIX@_MATH_H */
#endif /* _GL_INCLUDING_MATH_H */
#endif /* _@GUARD_PREFIX@_MATH_H */
#endif
