all: server client

server:
	gcc -Wall -Werror -Wextra -I . $@.c -o $@.out

client:
	gcc -Wall -Werror -Wextra -I . $@.c -o $@.out

clean:
	rm -rf *.out

fclean: clean

re: clean fclean all
