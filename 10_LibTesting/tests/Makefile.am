
TESTS_ENVIRONMENT = CK_VERBOSITY=$(CK_VERBOSITY)
TESTS = tests
check_PROGRAMS = tests

%.c: %.ts
	checkmk $< > $@

tests_CFLAGS = -I$(top_srcdir) @CHECK_CFLAGS@
tests_LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

CLEANFILES = tests.c