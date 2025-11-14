AC_PREREQ([2.71])
AC_INIT([guess_number], [0.0], [anyaf2003@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.26])

AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile po/Makefile.in])

AC_OUTPUT
