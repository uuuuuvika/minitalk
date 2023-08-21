
NAME=minitalk

LIBFT=libft/libft.a
FT_PRINTF=ft_printf/ft_printf.c

CC=cc
CFLAGS=-Wall -Wextra -Werror
RM=rm -rf

SRC_SERVER=server.c
SRC_CLIENT=client.c

OBJ_SERVER=$(SRCS_SERVER:.c=.o)
OBJ_CLIENT=$(SRCS_CLIENT:.c=.o)

all: $(SERVER) $(CLIENT)

$(NAME): all

$(FT_PRINTF):
				$(MAKE) -C ./ft_printf
$(LIBFT):
				$(MAKE) -C ./libft

$(SERVER): $(OBJ_SERVER) $(FT_PRINTF) $(LIBFT)
						$(CC) $(CFLAGS) $(OBJ_SERVER) $(FT_PRINTF) $(LIBFT) -o $(SERVER)
$(CLIENT): $(OBJ_CLIENT) $(FT_PRINTF) $(LIBFT)
						$(CC) $(CFLAGS) $(OBJ_CLIENT) $(FT_PRINTF) $(LIBFT) -o $(CLIENT)

clean:
		$(MAKE) clean -C ./ft_printf
		$(MAKE) clean -C ./libft
		$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
		$(MAKE) fclean -C ./ft_printf
		$(MAKE) fclean -C ./libft
		$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all bonus clean fclean re