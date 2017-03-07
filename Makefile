all:
	gcc -Wall -Werror -g -o miniDB main.c miniDB.c
clean:
	rm -f main
