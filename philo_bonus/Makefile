# BASIC SETTINGS :

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
AR = ar rcs

# SRCS :

SRCS = *.c */*.c

# PHILO SETTINGS :

NFLAGS = -lpthread
NAME = philo_bonus

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(NFLAGS) -o $(NAME)

clean:

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
