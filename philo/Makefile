NAME = philo

SRC = src/main.c src/init.c src/monitor.c src/philo.c src/utils.c

HDRS = incl/philo.h

OBJ = $(SRC:.c=.o)

RM = rm -f

%.o: %.c
	gcc -Wall -Wextra -Werror -Imlx -I ${HDRS} -c $< -o $@

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

all: $(NAME)
	make clean

clean:
	${RM} $(OBJ)

fclean: clean
	${RM} $(NAME) ${OBJ}

re: $(NAME)
	make clean

.PHONY: all clean fclean re
