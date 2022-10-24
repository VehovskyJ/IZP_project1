.PHONY : clean run rune-e run-num run-name test

t9search: t9search.c
	gcc -std=c99 -Wall -Wextra -Werror t9search.c -o t9search

clean:
	rm -f t9search

run: t9search
	./t9search 125 <seznam.txt

run-num: t9search
	./t9search 555 <seznam.txt

run-name: t9search
	./t9search 362 <seznam.txt

run-e: t9search
	./t9search <seznam.txt

test: t9search
	python3 test.py t9search