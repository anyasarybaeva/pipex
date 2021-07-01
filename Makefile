NAME=pipex
NAME_BONUS=pipex_bonus
CC=gcc
INCLUDE = -I include
HEADER = pipex.h
FLAGS = -Wall -Wextra -Werror
SRCS = main.c\
	fork.c\
	pipex.c\
	make_command\
	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c\

SRCS_BONUS = main.c\
	fork.c\
	pipex.c\
	make_command\
	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c\


OBJS =		${SRCS:.c=.o}
OBJS_BONUS =${SRCS_BONUS:.c=.o}
all: $(NAME)
%.o: %.c
	$(CC) -o $(FLAGS) ${INCLUDE} -c $<  -o $(<:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
			@make re -C libft	
			@cp libft/libft.a ./$(NAME)
			gcc -o $(NAME) $(OBJS) ${LIBA}/libft.a  ${INCLUDE}
bonus:	$(OBJS)
			@make re -C libft	
			@cp $(LIBA)/libft.a ./$(NAME)
			gcc -o $(NAME_BONUS) $(OBJS) ${LIBA}/libft.a ${INCLUDE}
clean:
		rm -f $(OBJS)

bonus_clean:
		rm -f $(OBJS)

fclean:	
			rm -f $(OBJS) $(NAME)

fclean_bonus:
			rm -f $(OBJS) $(NAME)

re:			fclean all

.PHONY:
			all bonus bonus_clean fclean_bonus clean fclean re
