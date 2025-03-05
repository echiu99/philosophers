NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -pthread -fsanitize=thread

SRC = main.c \
      init.c \
      utils.c \
      monitor.c \
      routine_actions.c \
      threads.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -fr $(OBJ)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean
