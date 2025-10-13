TRASH = range gdb_script_1_log.txt gdb_script_2_log.txt out_1.txt out_2.txt

range: range.c
	gcc -g -o0 range.c -w -o range

clean:
	rm -f $(TRASH)

test: range
	gdb -batch -x gdb_script_1.gdb > /dev/null 2>&1
	grep "^@@@" gdb_script_1_log.txt > out_1.txt
	cmp etalon_1.txt out_1.txt

	gdb -batch -x gdb_script_2.gdb > /dev/null 2>&1
	grep "^@@@" gdb_script_2_log.txt > out_2.txt
	cmp etalon_2.txt out_2.txt

