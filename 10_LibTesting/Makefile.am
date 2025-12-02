ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src tests

gitclean:
	git clean -xdf

coverage:
	lcov --gcov-tool gcov-13 --capture --directory . --output-file coverage.info
	lcov --summary coverage.info

.PHONY: coverage gitclean