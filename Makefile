CC      = cc
CFLAGS  = -Wall -Wextra -Werror

NAME    = pipex

SRCS    = pipex.c path.c utils.c
OBJS    = $(SRCS:.c=.o)

LIBFT_DIR = ./libft
LIBFT     = $(LIBFT_DIR)/libft.a

PRINTF_DIR = ./ft_printf
PRINTF     = $(PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
