NAME = philo
INCLUDE = philo.h
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -fsanitize=undefined -g
LDFLAGS = -lpthread
SRC = main.c init.c string.c utils.c monitor.c thread_work.c setter.c getter.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
