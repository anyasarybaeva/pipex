NAME = pipex
NAME_BONUS = pipex_bonus
CC = gcc
INCLUDE = -I include
HEADER = pipex.h
FLAGS = -Wall -Wextra -Werror
LIBA = libft
SRCS = 	$(addprefix src/,\
	main.c fork.c pipex.c make_command.c)\
	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c\

SRCS_BONUS = $(addprefix bonus/,\
	main_bonus.c fork_bonus.c pipex_bonus.c make_command_bonus.c)\
	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c\

OBJS =	${SRCS:.c=.o}

OBJS_BONUS =${SRCS_BONUS:.c=.o}

%.o: %.c
	$(CC) -o $(FLAGS) ${INCLUDE} -c $<  -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			@make re -C libft	
			@cp $(LIBA)/libft.a ./$(NAME)
			gcc -o $(NAME) $(OBJS) ${LIBA}/libft.a ${INCLUDE}

bonus:		$(OBJS_BONUS)
			@make re -C libft	
			@cp $(LIBA)/libft.a ./$(NAME)
			gcc -o $(NAME_BONUS) $(OBJS_BONUS) ${LIBA}/libft.a ${INCLUDE}


clean:
		rm -f $(OBJS)

bonus_clean:
		rm -f $(OBJS_BONUS)

fclean:	
			rm -f $(OBJS) $(NAME)

fclean_bonus:
			rm -f $(OBJS_BONUS) $(NAME_BONUS)

re:			fclean all

re_bonus:
	fclean_bonus bonus
.PHONY:
			all bonus bonus_clean fclean_bonus clean fclean re re_bonus
