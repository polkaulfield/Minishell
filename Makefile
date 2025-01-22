NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g
LIBFTDIR = libft/
OBJ_DIR = obj/

SRC = src/*.c

OBJ = ${SRC:.c=.o}

INCLUDE = -L ./libft -lft -lreadline

%.o: %.c Makefile includes/minishell.h libft/libft.a
			${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all: make_libs ${NAME}

make_libs:
	make -C $(LIBFTDIR)

${NAME}: ${OBJ}
			${CC} ${FLAGS} ${OBJ} -o ${NAME} ${INCLUDE}

clean:
		${RM} ${OBJ}
		@cd $(LIBFTDIR) && $(MAKE) clean

fclean: clean
		${RM} ${NAME}
		@cd $(LIBFTDIR) && $(MAKE) fclean

re: clean all

.PHONY: all clean fclean re
