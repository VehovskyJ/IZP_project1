t9search: t9search.c
	gcc -std=c99 -Wall -Wextra -Werror t9search.c -o t9search

clean:
	rm -f t9search

run:
	./t9search 125 <seznam.txt