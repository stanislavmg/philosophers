NAME = philo_bonus
INCLUDE = philo_bonus.h
CFLAGS = -Wall -Wextra -Werror -g3
SRC = main.c init.c string.c utils.c routine.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME) : $(OBJ) $(INCLUDE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re
