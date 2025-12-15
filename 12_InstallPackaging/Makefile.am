AM_CPPFLAGS=-D'LOCALEDIR="$(localedir)"'

bin_PROGRAMS = guess

guess_SOURCES = src/guess.c
guess_LDADD = roman/libroman.la
guess_CPPFLAGS = -I$(top_srcdir)/roman

SUBDIRS = po test roman

clean:
	git clean -xdf