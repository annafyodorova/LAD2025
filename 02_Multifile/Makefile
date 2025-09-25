TRASH = *.o prog prog-a prog-so liboutput* out_prog*

%.o: %.c
	cc -c $< -o $@

fun_pic.o: fun.c
	cc -fPIC -c $< -o $@

const_pic.o: const.c
	cc -fPIC -c $< -o $@

prog: const.o fun.o prog.o
	cc -o $@ $^

prog-a: prog.o liboutput_static.a
	cc -o $@ $^

prog-so: prog.o liboutput.so
	cc -o $@ $< -L. -loutput

clean:
	rm -f $(TRASH)

liboutput_static.a: fun.o const.o
	ar rcs $@ $^

liboutput.so: fun_pic.o const_pic.o
	cc -shared $^ -o $@

.PHONY: all
all: prog prog-a prog-so

.PHONY: test
test: prog prog-a prog-so
	./prog > out_prog_0 2>&1
	./prog arg1 > out_prog_1 2>&1
	./prog arg1 arg2 arg3 > out_prog_3 2>&1

	./prog-a > out_proga_0 2>&1
	./prog-a arg1 > out_proga_1 2>&1
	./prog-a arg1 arg2 arg3 > out_proga_3 2>&1

	LD_LIBRARY_PATH=. ./prog-so > out_progso_0 2>&1
	LD_LIBRARY_PATH=. ./prog-so arg1 > out_progso_1 2>&1
	LD_LIBRARY_PATH=. ./prog-so arg1 arg2 arg3 > out_progso_3 2>&1

	cmp out_prog_0 out_proga_0
	cmp out_prog_0 out_progso_0
	cmp out_progso_0 out_proga_0

	cmp out_prog_1 out_proga_1
	cmp out_prog_1 out_progso_1
	cmp out_proga_1 out_progso_1
	
	cmp out_prog_3 out_proga_3
	cmp out_prog_3 out_progso_3
	cmp out_proga_3 out_progso_3
