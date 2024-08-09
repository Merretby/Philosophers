NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra  #-fsanitize=thread
CFILES = philosophers.c parsing.c init.c life_of_philo.c helper.c
OFILSE = $(CFILES:.c=.o)
LIB=./philosophers.h

all: $(NAME)

$(NAME): $(OFILSE) $(LIB)
	$(CC) $(CFLAGS) $(OFILSE) -o $(NAME)

clean:
	rm -f $(OFILSE)

fclean: clean
	rm -f $(NAME)

re: fclean all
