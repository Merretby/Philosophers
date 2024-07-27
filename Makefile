NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address -pthread -I.
CFILES = philosophers.c parsing.c init.c
OFILSE = $(CFILES:.c=.o)


all: $(NAME)

$(NAME): $(OFILSE)
	$(CC) $(CFLAGS) $(OFILSE) -o $(NAME)

clean:
	rm -f $(OFILSE)

fclean: clean
	rm -f $(NAME)

re: fclean all

push :
	@make fclean
	@git add .
	@git commit -m "news"
	@git push -f