NAME	= libftprintf.a

SRCS	= ft_printf.c	ft_putadr.c	ft_puthex.c	ft_putnbr.c	ft_puttext.c	ft_putunsigned.c

OBJS	= $(SRCS:.c=.o)

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJS)
	ar -cr $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re
