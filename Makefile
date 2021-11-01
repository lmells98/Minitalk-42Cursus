CFLAGS	= -Wall -Werror -Wextra -g
CC		= gcc

SRVR	= $(SRC)/server.c
CLNT	= $(SRC)/client.c

SRC		= ./srcs
PRNTF	= $(SRC)/ft_printf/libftprintf.a

BONUS	= $(SRC)/bonus
B		= $(BONUS)

all: m

m: server client

b: $(PRNTF)
	$(CC) $(CFLAGS) -I $(B) $(BONUS)/server_bonus.c $(PRNTF) -o server
	$(CC) $(CFLAGS) -I $(B) $(BONUS)/client_bonus.c $(PRNTF) -o client

server: $(PRNTF)
	$(CC) $(CFLAGS) -I . $(SRVR) $(PRNTF) -o server

client: $(PRNTF)
	$(CC) $(CFLAGS) -I . $(CLNT) $(PRNTF) -o client

$(PRNTF):
	make -C $(SRC)/ft_printf libftprintf.a

clean:
	make -C $(SRC)/ft_printf/ clean
	rm -rf client

fclean: clean
	make -C $(SRC)/ft_printf/ fclean
	rm -rf *.dSYM
	rm -rf server

re: clean fclean b
