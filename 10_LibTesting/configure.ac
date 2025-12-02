# configure.ac
AC_PREREQ([2.69])
AC_INIT([growable-buf], [1.0], [your@email])
AM_INIT_AUTOMAKE([foreign -Wall])
AC_CONFIG_MACRO_DIRS([m4])
LT_INIT

AC_CONFIG_SRCDIR([src/growable_buf.c])
AC_CONFIG_HEADERS([config.h])

# Programs
AC_PROG_CC
AM_PROG_AR

# Headers
AC_CHECK_HEADERS([stddef.h stdlib.h])
AC_CHECK_DECLS([offsetof], [], [AC_MSG_ERROR([offsetof not available])], [[#include <stddef.h>]])

# Types
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Functions
AC_FUNC_MALLOC
AC_FUNC_REALLOC

# Check for Check framework (optional, for tests)
PKG_CHECK_MODULES([CHECK], [check >= 0.9.6], [], [:])

# Gcov support
AC_ARG_ENABLE([gcov],
  [AS_HELP_STRING([--enable-gcov], [enable test coverage])],
  [],
  [enable_gcov=no]
)
AM_CONDITIONAL([COND_GCOV], [test "x$enable_gcov" != xno])

AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_OUTPUT