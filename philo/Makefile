# BASIC SETTINGS :

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
CC = cc
RM = rm -rf
AR = ar rcs

# SRCS :

SRCS = main.c Pars_Utils/ft_atol.c Pars_Utils/pars_arg.c Pars_Utils/stderr.c Phil_Utils/create_utils.c Phil_Utils/create.c Phil_Utils/error.c Phil_Utils/gettime.c Phil_Utils/thread.c Phil_Utils/thread_utils.c Phil_Utils/create_utils2.c

# PHILO SETTINGS :

NFLAGS = -pthread
NAME = philo

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(NFLAGS) -o $(NAME)

clean:

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
