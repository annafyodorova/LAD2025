TARGET = esub
TEST=test_

esub: esub.c
	gcc -O0 -Wall -o $@ $<

clean:
	rm -f esub $(TEST)1 $(TEST)2 $(TEST)3

test: esub
	@echo 'abc' | sed -E 's/a(b)c/X\1Y/' > $(TEST)1
	@./esub 'a(b)c' 'X\1Y' 'abc' | cmp - $(TEST)1 >/dev/null && echo "Test 1 passed"

	@echo 'a' | sed -E 's/a/\\/' > $(TEST)2
	@./esub 'a' '\\' 'a' | cmp - $(TEST)2 >/dev/null && echo "Test 2 passed"

	@echo 'воскресенье, 19 октября 2025 г. 21:06:43 (MSK)' | sed 's/\([0-9][0-9]*\)/<\1>/' > $(TEST)3
	@./esub '([0-9][0-9]*)' '<\1>' 'воскресенье, 19 октября 2025 г. 21:06:43 (MSK)' | cmp - $(TEST)3 >/dev/null && echo "Test 3 passed"


