AC_PREREQ([2.69])
AC_INIT([rhasher], [0.1], [])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_SRCDIR([src/rhasher.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

PKG_CHECK_MODULES([RHASH], [librhash >= 1.0])

AC_ARG_ENABLE([readline],
  [AS_HELP_STRING([--disable-readline], [do not use readline])],
  [],
  [enable_readline=yes]
)

AC_CHECK_HEADERS([unistd.h rhash.h readline/readline.h])

AS_IF([test "x$enable_readline" != "xno"],
  [AC_CHECK_HEADERS([readline/readline.h])
   AC_CHECK_LIB([readline], [readline],
     [have_readline=yes],
     [have_readline=no])
   AS_IF([test "x$have_readline" = "xyes" && test "x$ac_cv_header_readline_readline_h" = "xyes"],
     [AC_DEFINE([READLINE], [1], [Use readline])
      READLINE_LIBS="-lreadline"
     ],
     [AC_MSG_WARN([readline support disabled])])
  ]
)

AC_SUBST([READLINE_LIBS])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT