NAME = philo
CFLAGS = -Wextra -Wall -Werror -g -MMD
CC = gcc $(CFLAGS) $(INCLUDE) 
INCLUDE	= -I ./includes 
SRC_DIR = src
OBJ_DIR = obj

#FILES
SRC_FILES = $(SRC_DIR)/main.c \
			$(SRC_DIR)/error.c \
			$(SRC_DIR)/init.c \
			$(SRC_DIR)/parse_input.c \



#OBJ/DEP
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
# DEP = $(addsuffix .d, $(basename $(SRC_FILES)))

#RULES
all: $(NAME)

$(OBJ_DIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@

$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(NAME)

clean:
	$(RM) $(OBJ) $(DEP) $(BONUS_OBJ) $(BONUS_DEP)
	rm -rf ./$(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus