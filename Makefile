CFLAGS	= -Wall -Werror -Wextra -g
CC		= gcc

SRVR	= $(SRC_DIR)/server.c
CLNT	= $(SRC_DIR)/client.c

SRC_DIR	= ./srcs
PRNTF	= $(SRC_DIR)/ft_printf/libftprintf.a

all: server client

server: $(PRNTF)
	$(CC) $(CFLAGS) -I . $(SRVR) $(PRNTF) -o server

client: $(PRNTF)
	$(CC) $(CFLAGS) -I . $(CLNT) $(PRNTF) -o client

$(PRNTF):
	make -C $(SRC_DIR)/ft_printf libftprintf.a

clean:
	make -C $(SRC_DIR)/ft_printf/ clean
	rm -rf client

fclean: clean
	make -C $(SRC_DIR)/ft_printf/ fclean
	rm -rf server


re: clean fclean all
