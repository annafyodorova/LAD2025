TEST=test_

all: move preload

move: move.c
	gcc -O0 move.c -o move

preload: preload.c
	gcc -shared -o preload.so preload.c

test: move preload
	@echo "Test 1: open outfile fails"
	echo hello > in
	strace -e inject=openat:error=EACCES:when=34 ./move in test_out 2> $(TEST)1 || true
	grep -q "+++ exited with 2" $(TEST)1 && test -f in && echo "TEST #1 PASSED" || (echo "TEST #1 FAILED"; exit 1)

	@echo "Test 2: read fails"
	echo hello > in
	strace -e inject=read:error=EIO:when=3 ./move in test_out 2> $(TEST)2 || true
	grep -q "+++ exited with 5 +++" $(TEST)2 && test -f in && echo "TEST #2 PASSED" || (echo "TEST #2 FAILED"; exit 1)

	@echo "Test 3: close fails"
	echo hello > in
	strace -e inject=close:error=EIO:when=5 ./move in test_out 2> $(TEST)3 || true
	grep -q "+++ exited with 3 +++" $(TEST)3 && test -f in && echo "TEST #3 PASSED" || (echo "TEST #3 FAILED"; exit 1)

	@echo "Test 4: PROTECT file not removed"
	echo "protected content" > test_PROTECT.txt
	LD_PRELOAD=$(CURDIR)/preload.so ./move test_PROTECT.txt test_out.txt 2>/dev/null
	test -f test_PROTECT.txt && test -f test_out.txt && echo "TEST #4 PASSED" || (echo "TEST #4 FAILED"; exit 1)

clean:
	rm -f *.o move *.so *.txt $(TEST)* in test_out