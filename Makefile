NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g
LIBFTDIR = libft/
OBJ_DIR = obj/

# Source files
SRC = $(wildcard src/*.c)
# Object files (placed in OBJ_DIR)
OBJ = ${SRC:.c=.o}

# Include and library paths
INCLUDES = -I includes -I $(LIBFTDIR)
LIBS = -L $(LIBFTDIR) -lft -lreadline

# Ensure OBJ_DIR exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule to compile object files
$(OBJ_DIR)%.o: src/%.c includes/minishell.h libft/libft.a | $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# Build libft
make_libs:
	@make -C $(LIBFTDIR)

# Build minishell
all: make_libs $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBS)

# Clean up
clean:
	$(RM) $(OBJ)
	@make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all make_libs clean fclean re
