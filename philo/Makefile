NAME = philo
INCLUDE = philo.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lpthread
SRC = main.c init.c string.c utils.c monitor.c thread_work.c
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
