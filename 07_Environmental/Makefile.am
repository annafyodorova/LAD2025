ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = rhasher
rhasher_SOURCES = src/rhasher.c
rhasher_CFLAGS = $(RHASH_CFLAGS)
rhasher_LDADD = $(RHASH_LIBS) $(READLINE_LIBS)

# Clean generated files
CLEANFILES =
DISTCLEANFILES = config.h.in

# check_PROGRAMS =
# TESTS =
# EXTRA_DIST =