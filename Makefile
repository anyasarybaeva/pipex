CC = gcc
LFT_DIR = libft/
CFLAGS = -Wall -Wextra -Werror -O2  -I $(LFT_DIR)
HEADER = $(LFT_DIR)libft.h
NAME = pipex
SRCS = main.c fork.c pipex.c make_command.c\
	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c\
OBJS = $(SRCS:.c=.o)
LIBFT = $(LFT_DIR)libft.a
ALL_LIB = -L $(LFT_DIR) -lft

all: lft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(ALL_LIB) -g -o $@

%.o: %.c $(HEADER) $(LIBFT) Makefile
	$(CC) $(CFLAGS) -c $< -o $@
lft:
	@$(MAKE) -j -C libft
clean:
	rm -f $(OBJS)
	@$(MAKE) clean -j -C libft
fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -j -C libft
re: fclean all

.PHONY: all clean fclean re