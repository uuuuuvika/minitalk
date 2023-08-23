NAME=minitalk

SERVER=server
CLIENT=client

LIBFT=lib/libft.a
FT_PRINTF=ft_p/libftprintf.a

CC=cc
CFLAGS=-Wall -Wextra -Werror
RM=rm -rf

SRC_SERVER=server.c
SRC_CLIENT=client.c

OBJ_SERVER=$(SRC_SERVER:.c=.o)
OBJ_CLIENT=$(SRC_CLIENT:.c=.o)

all: $(SERVER) $(CLIENT)
# $(NAME): all

$(LIBFT):
	$(MAKE) -C ./lib
$(FT_PRINTF):
	$(MAKE) -C ./ft_p

$(SERVER): $(OBJ_SERVER) $(FT_PRINTF) $(LIBFT)
						$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) $(FT_PRINTF) -o server
$(CLIENT): $(OBJ_CLIENT) $(FT_PRINTF) $(LIBFT)
						$(CC) $(CFLAGS) $(OBJ_CLIENT)  $(LIBFT) $(FT_PRINTF) -o client
clean:
		$(MAKE) clean -C ./ft_p
		$(MAKE) clean -C ./lib
		$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
		$(MAKE) fclean -C ./ft_p
		$(MAKE) fclean -C ./lib
		$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all bonus clean fclean re