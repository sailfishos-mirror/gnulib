# locale-fr.m4
# serial 24
dnl Copyright (C) 2003, 2005-2025 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

dnl From Bruno Haible.

dnl Determine the name of a french locale with traditional encoding.
AC_DEFUN_ONCE([gt_LOCALE_FR],
[
  AC_REQUIRE([AC_CANONICAL_HOST])
  AC_REQUIRE([AM_LANGINFO_CODESET])
  AC_CACHE_CHECK([for a traditional french locale], [gt_cv_locale_fr], [
    AC_LANG_CONFTEST([AC_LANG_SOURCE([[
#include <locale.h>
#include <time.h>
#if HAVE_LANGINFO_CODESET
# include <langinfo.h>
#endif
#include <stdlib.h>
#include <string.h>
struct tm t;
char buf[16];
int main () {
  /* On BeOS and Haiku, locales are not implemented in libc.  Rather, libintl
     imitates locale dependent behaviour by looking at the environment
     variables, and all locales use the UTF-8 encoding.  */
#if defined __BEOS__ || defined __HAIKU__
  return 1;
#else
  /* Check whether the given locale name is recognized by the system.  */
# if defined _WIN32 && !defined __CYGWIN__
  /* On native Windows, setlocale(category, "") looks at the system settings,
     not at the environment variables.  Also, when an encoding suffix such
     as ".65001" or ".54936" is specified, it succeeds but sets the LC_CTYPE
     category of the locale to "C".  */
  if (setlocale (LC_ALL, getenv ("LC_ALL")) == NULL
      || strcmp (setlocale (LC_CTYPE, NULL), "C") == 0)
    return 1;
# else
  if (setlocale (LC_ALL, "") == NULL) return 1;
# endif
  /* Check whether nl_langinfo(CODESET) is nonempty and not "ASCII" or "646".
     On Mac OS X 10.3.5 (Darwin 7.5) in the fr_FR locale, nl_langinfo(CODESET)
     is empty, and the behaviour of Tcl 8.4 in this locale is not useful.
     On OpenBSD 4.0, when an unsupported locale is specified, setlocale()
     succeeds but then nl_langinfo(CODESET) is "646". In this situation,
     some unit tests fail.
     On MirBSD 10, when an unsupported locale is specified, setlocale()
     succeeds but then nl_langinfo(CODESET) is "UTF-8".  */
# if HAVE_LANGINFO_CODESET
  {
    const char *cs = nl_langinfo (CODESET);
    if (cs[0] == '\0' || strcmp (cs, "ASCII") == 0 || strcmp (cs, "646") == 0
        || strcmp (cs, "UTF-8") == 0)
      return 1;
  }
# endif
# ifdef __CYGWIN__
  /* On Cygwin, avoid locale names without encoding suffix, because the
     locale_charset() function relies on the encoding suffix.  Note that
     LC_ALL is set on the command line.  */
  if (strchr (getenv ("LC_ALL"), '.') == NULL) return 1;
# endif
  /* Check whether in the abbreviation of the second month, the second
     character (should be U+00E9: LATIN SMALL LETTER E WITH ACUTE) is only
     one byte long. This excludes the UTF-8 encoding.  */
  t.tm_year = 1975 - 1900; t.tm_mon = 2 - 1; t.tm_mday = 4;
  if (strftime (buf, sizeof (buf), "%b", &t) < 3 || buf[2] != 'v') return 1;
# if !defined __BIONIC__ /* Bionic libc's 'struct lconv' is just a dummy.  */
  /* Check whether the decimal separator is a comma.
     On NetBSD 3.0 in the fr_FR.ISO8859-1 locale
     and on Haiku in the fr_FR.UTF-8 locale,
     localeconv()->decimal_point are nl_langinfo(RADIXCHAR) are both ".".  */
  if (localeconv () ->decimal_point[0] != ',') return 1;
# endif
  return 0;
#endif
}
      ]])])
    if AC_TRY_EVAL([ac_link]) && test -s conftest$ac_exeext; then
      case "$host_os" in
        # Handle native Windows specially, because there setlocale() interprets
        # "ar" or "ara" as "Arabic" or "Arabic_Saudi Arabia.1256",
        # "en" or "eng" as "English" or "English_United States.1252",
        # "fr" or "fra" as "French" or "French_France.1252",
        # "ge"(!) or "deu"(!) as "German" or "German_Germany.1252",
        # "ja" or "jpn" as "Japanese" or "Japanese_Japan.932",
        # and similar.
        mingw* | windows*)
          # Test for the native Windows locale name.
          if (LC_ALL=French_France.1252 LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
            gt_cv_locale_fr=French_France.1252
          else
            # None found.
            gt_cv_locale_fr=none
          fi
          ;;
        *)
          # Setting LC_ALL is not enough. Need to set LC_TIME to empty, because
          # otherwise on Mac OS X 10.3.5 the LC_TIME=C from the beginning of the
          # configure script would override the LC_ALL setting. Likewise for
          # LC_CTYPE, which is also set at the beginning of the configure script.
          # Test for the usual locale name.
          if (LC_ALL=fr_FR LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
            gt_cv_locale_fr=fr_FR
          else
            # Test for the locale name with explicit encoding suffix.
            if (LC_ALL=fr_FR.ISO-8859-1 LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
              gt_cv_locale_fr=fr_FR.ISO-8859-1
            else
              # Test for the AIX, OSF/1, FreeBSD, NetBSD, OpenBSD locale name.
              if (LC_ALL=fr_FR.ISO8859-1 LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
                gt_cv_locale_fr=fr_FR.ISO8859-1
              else
                # Test for the HP-UX locale name.
                if (LC_ALL=fr_FR.iso88591 LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
                  gt_cv_locale_fr=fr_FR.iso88591
                else
                  # Test for the Solaris 10 locale name.
                  if (LC_ALL=fr LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
                    gt_cv_locale_fr=fr
                  else
                    # None found.
                    gt_cv_locale_fr=none
                  fi
                fi
              fi
            fi
          fi
          ;;
      esac
    fi
    rm -fr conftest*
  ])
  LOCALE_FR=$gt_cv_locale_fr
  case $LOCALE_FR in #(
    '' | *[[[:space:]\"\$\'*@<:@]]*)
      dnl This locale name might cause trouble with sh or make.
      AC_MSG_WARN([invalid locale "$LOCALE_FR"; assuming "none"])
      LOCALE_FR=none;;
  esac
  AC_SUBST([LOCALE_FR])
])

dnl Determine the name of a french locale with UTF-8 encoding.
AC_DEFUN_ONCE([gt_LOCALE_FR_UTF8],
[
  AC_REQUIRE([AC_CANONICAL_HOST])
  AC_REQUIRE([AM_LANGINFO_CODESET])
  AC_CACHE_CHECK([for a french Unicode locale], [gt_cv_locale_fr_utf8], [
    case "$host_os" in
      *-musl* | midipix*)
        dnl On musl libc, all kinds of ll_CC.UTF-8 locales exist, even without
        dnl any locale file on disk. But they are effectively equivalent to the
        dnl C.UTF-8 locale, except for locale categories (such as LC_MESSSAGES)
        dnl for which localizations (.mo files) have been installed.
        gt_cv_locale_fr_utf8=fr_FR.UTF-8
        ;;
      *)
        AC_LANG_CONFTEST([AC_LANG_SOURCE([[
#include <locale.h>
#include <time.h>
#if HAVE_LANGINFO_CODESET
# include <langinfo.h>
#endif
#include <stdlib.h>
#include <string.h>
struct tm t;
char buf[16];
int main () {
  /* On BeOS and Haiku, locales are not implemented in libc.  Rather, libintl
     imitates locale dependent behaviour by looking at the environment
     variables, and all locales use the UTF-8 encoding.  */
#if !(defined __BEOS__ || defined __HAIKU__)
  /* Check whether the given locale name is recognized by the system.  */
# if defined _WIN32 && !defined __CYGWIN__
  /* On native Windows, setlocale(category, "") looks at the system settings,
     not at the environment variables.  Also, when an encoding suffix such
     as ".65001" or ".54936" is specified, it succeeds but sets the LC_CTYPE
     category of the locale to "C".  */
  if (setlocale (LC_ALL, getenv ("LC_ALL")) == NULL
      || strcmp (setlocale (LC_CTYPE, NULL), "C") == 0)
    return 1;
# else
  if (setlocale (LC_ALL, "") == NULL) return 1;
# endif
  /* Check whether nl_langinfo(CODESET) is nonempty and not "ASCII" or "646".
     On Mac OS X 10.3.5 (Darwin 7.5) in the fr_FR locale, nl_langinfo(CODESET)
     is empty, and the behaviour of Tcl 8.4 in this locale is not useful.
     On OpenBSD 4.0, when an unsupported locale is specified, setlocale()
     succeeds but then nl_langinfo(CODESET) is "646". In this situation,
     some unit tests fail.  */
# if HAVE_LANGINFO_CODESET
  {
    const char *cs = nl_langinfo (CODESET);
    if (cs[0] == '\0' || strcmp (cs, "ASCII") == 0 || strcmp (cs, "646") == 0)
      return 1;
  }
# endif
# ifdef __CYGWIN__
  /* On Cygwin, avoid locale names without encoding suffix, because the
     locale_charset() function relies on the encoding suffix.  Note that
     LC_ALL is set on the command line.  */
  if (strchr (getenv ("LC_ALL"), '.') == NULL) return 1;
# endif
  /* Check whether in the abbreviation of the second month, the second
     character (should be U+00E9: LATIN SMALL LETTER E WITH ACUTE) is
     two bytes long, with UTF-8 encoding.  */
  t.tm_year = 1975 - 1900; t.tm_mon = 2 - 1; t.tm_mday = 4;
  if (strftime (buf, sizeof (buf), "%b", &t) < 4
      || buf[1] != (char) 0xc3 || buf[2] != (char) 0xa9 || buf[3] != 'v')
    return 1;
#endif
#if !defined __BIONIC__ /* Bionic libc's 'struct lconv' is just a dummy.  */
  /* Check whether the decimal separator is a comma.
     On NetBSD 3.0 in the fr_FR.ISO8859-1 locale
     and on Haiku in the fr_FR.UTF-8 locale,
     localeconv()->decimal_point are nl_langinfo(RADIXCHAR) are both ".".  */
  if (localeconv () ->decimal_point[0] != ',') return 1;
#endif
  return 0;
}
          ]])])
        if AC_TRY_EVAL([ac_link]) && test -s conftest$ac_exeext; then
          case "$host_os" in
            # Handle native Windows specially, because there setlocale() interprets
            # "ar" or "ara" as "Arabic" or "Arabic_Saudi Arabia.1256",
            # "en" or "eng" as "English" or "English_United States.1252",
            # "fr" or "fra" as "French" or "French_France.1252",
            # "ge"(!) or "deu"(!) as "German" or "German_Germany.1252",
            # "ja" or "jpn" as "Japanese" or "Japanese_Japan.932",
            # and similar.
            mingw* | windows*)
              # Test for the hypothetical native Windows locale name.
              if (LC_ALL=French_France.65001 LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
                gt_cv_locale_fr_utf8=French_France.65001
              else
                # None found.
                gt_cv_locale_fr_utf8=none
              fi
              ;;
            *)
              # Setting LC_ALL is not enough. Need to set LC_TIME to empty, because
              # otherwise on Mac OS X 10.3.5 the LC_TIME=C from the beginning of the
              # configure script would override the LC_ALL setting. Likewise for
              # LC_CTYPE, which is also set at the beginning of the configure script.
              # Test for the usual locale name.
              if (LC_ALL=fr_FR LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
                gt_cv_locale_fr_utf8=fr_FR
              else
                # Test for the locale name with explicit encoding suffix.
                if (LC_ALL=fr_FR.UTF-8 LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
                  gt_cv_locale_fr_utf8=fr_FR.UTF-8
                else
                  # Test for the Solaris 10 locale name.
                  if (LC_ALL=fr.UTF-8 LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
                    gt_cv_locale_fr_utf8=fr.UTF-8
                  else
                    # None found.
                    gt_cv_locale_fr_utf8=none
                  fi
                fi
              fi
              ;;
          esac
        fi
        rm -fr conftest*
        ;;
    esac
  ])
  LOCALE_FR_UTF8=$gt_cv_locale_fr_utf8
  case $LOCALE_FR_UTF8 in #(
    '' | *[[[:space:]\"\$\'*@<:@]]*)
      dnl This locale name might cause trouble with sh or make.
      AC_MSG_WARN([invalid locale "$LOCALE_FR_UTF8"; assuming "none"])
      LOCALE_FR_UTF8=none;;
  esac
  AC_SUBST([LOCALE_FR_UTF8])

  dnl Users of $LOCALE_FR_UTF8 need to know which of the locale categories they
  dnl can rely on.
  case "$host_os" in
    *-musl* | midipix*)
      dnl On musl libc, locale categories other than LC_CTYPE and LC_MESSAGES
      dnl are effectively unimplemented.
      LC_COLLATE_IMPLEMENTED=false
      LC_NUMERIC_IMPLEMENTED=false
      LC_TIME_IMPLEMENTED=false
      LC_MONETARY_IMPLEMENTED=false
      ;;
    *)
      LC_COLLATE_IMPLEMENTED=true
      LC_NUMERIC_IMPLEMENTED=true
      LC_TIME_IMPLEMENTED=true
      LC_MONETARY_IMPLEMENTED=true
      ;;
  esac
  AC_SUBST([LC_COLLATE_IMPLEMENTED])
  AC_SUBST([LC_NUMERIC_IMPLEMENTED])
  AC_SUBST([LC_TIME_IMPLEMENTED])
  AC_SUBST([LC_MONETARY_IMPLEMENTED])
])
