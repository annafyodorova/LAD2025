AC_PREREQ([2.69])
AC_INIT([libbuf], [1.0], [])
AM_INIT_AUTOMAKE([foreign -Wall])
AC_CONFIG_MACRO_DIRS([m4])

AC_CONFIG_SRCDIR([src/libbuf.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC
AM_PROG_AR

LT_INIT

AC_CHECK_HEADERS([stddef.h stdlib.h])
AC_CHECK_DECLS([offsetof], [], [AC_MSG_ERROR([offsetof not available])], [[#include <stddef.h>]])

AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

AC_FUNC_MALLOC
AC_FUNC_REALLOC

PKG_CHECK_MODULES([CHECK], [check >= 0.9.6], [], [:])

AC_ARG_ENABLE([gcov],
  [AS_HELP_STRING([--enable-gcov], [enable test coverage])],
  [],
  [enable_gcov=no]
)
AM_CONDITIONAL([COND_GCOV], [test "x$enable_gcov" != xno])

if test "x$enable_gcov" = xyes; then
  AC_MSG_CHECKING([whether compiler supports gcov])
  save_CFLAGS="$CFLAGS"
  save_LDFLAGS="$LDFLAGS"
  CFLAGS="$CFLAGS -fprofile-arcs -ftest-coverage"
  LDFLAGS="$LDFLAGS -fprofile-arcs -ftest-coverage"
  AC_LINK_IFELSE([
    AC_LANG_PROGRAM([[]], [[]])
  ], [
    AC_MSG_RESULT([yes])
    GCOV_CFLAGS="-fprofile-arcs -ftest-coverage"
    GCOV_LDFLAGS="-fprofile-arcs -ftest-coverage"
    AC_SUBST([GCOV_CFLAGS])
    AC_SUBST([GCOV_LDFLAGS])
  ], [
    AC_MSG_RESULT([no])
    AC_MSG_ERROR([gcov support requested but compiler doesn't support it])
  ])
  CFLAGS="$save_CFLAGS"
  LDFLAGS="$save_LDFLAGS"
fi

AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_OUTPUT