ACLOCAL_AMFLAGS = -I m4

AUTOMAKE_OPTIONS = foreign subdir-objects

bin_PROGRAMS = rhasher
rhasher_SOURCES = src/rhasher.c
rhasher_CFLAGS = $(RHASH_CFLAGS)
rhasher_LDADD = $(RHASH_LIBS) $(READLINE_LIBS)

CLEANFILES =

.PHONY: check
check: rhasher
	@echo "Hello, LAD2025!" > t.txt
	@echo "Testing SHA1"
	@ref=$$(sha1sum t.txt | cut -d' ' -f1); \
	out=$$(echo 'SHA1 t.txt' | ./rhasher | tail -n1); \
	if [ "$$ref" = "$$out" ]; then \
		echo "PASS: SHA1"; \
	else \
		echo "FAIL: SHA1"; \
		exit 1; \
	fi
	@echo "Testing MD5"
	@ref=$$(md5sum t.txt | cut -d' ' -f1); \
	out=$$(echo 'MD5 t.txt' | ./rhasher | tail -n1); \
	if [ "$$ref" = "$$out" ]; then \
		echo "PASS: MD5"; \
	else \
		echo "FAIL: MD5"; \
		exit 1; \
	fi
	@echo "All tests passed!"

gitclean:
	git clean -xdf