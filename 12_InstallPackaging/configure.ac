AC_PREREQ([2.71])
AC_INIT([guess], [0.0], [])


AM_INIT_AUTOMAKE([foreign subdir-objects])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION(0.21)

AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])

AC_SUBST(GETTEXT_PACKAGE, "$PACKAGE")

ALL_LINGUAS="ru"

AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

AC_PROG_CC
LT_INIT
IT_PROG_INTLTOOL([0.35.0])

AC_CONFIG_FILES([Makefile po/Makefile.in test/Makefile])
AC_OUTPUT
