t9search: t9search.c
	gcc -std=c99 -Wall -Wextra -Werror t9search.c -o t9search

clean:
	rm -f t9search

run:
	./t9search 125 <seznam.txt

run-num:
	./t9search 555 <seznam.txt

run-name:
	./t9search 362 <seznam.txt

run-e:
	./t9search <seznam.txt