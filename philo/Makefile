CC = cc
FLAGS = -Wall -Wextra -Werror -Iinc -pthread

SRCS = srcs/main.c \
	   srcs/parsing/parser.c \
	   srcs/parsing/ft_atoi.c \
	   srcs/exec/exec.c \
	   srcs/exec/philo_routine.c \
	   srcs/exec/philosopher_utils.c \
	   srcs/exec/philosopher_actions.c \
	   srcs/exec/return_error.c

OBJS_DIR = objects/
OBJS = $(patsubst srcs/%.c, $(OBJS_DIR)%.o, $(SRCS))

HEADER = inc/philosopher.h

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

$(OBJS_DIR)%.o: srcs/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
