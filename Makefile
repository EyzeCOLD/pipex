#####  FILES  ##################################################################

NAME := ./bin/pipex

SRC_DIR := ./src/
SRC :=	arg_split.c		get_av.c		get_env_path.c	\
		main.c			pipex.c			open_file.c	\
		error.c			exec_commands.c	free_av.c
SRC := $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR := ./obj/
OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

INC := ./inc/pipex.h

LIB := libft/libft.a

#  BONUS

BONUS := ./bin/pipex_bonus

BONUS_SRC := arg_split.c	get_av.c		get_env_path.c	\
			 main_bonus.c	pipex.c			open_file.c	\
			 error.c		exec_commands.c	heredoc_bonus.c	\
			 free_av.c
BONUS_SRC := $(addprefix $(SRC_DIR), $(BONUS_SRC))

BONUS_OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(BONUS_SRC))

BONUS_INC := $(INC) ./inc/heredoc_bonus.h

#  DEBUG

DEBUG := ./debug/pipex

DEBUG_BONUS := ./debug/pipex_bonus

#####  COMPILERS  ##############################################################

CC := cc

CFLAGS := -Wall -Wextra -Werror

DEBUG_FLAGS := -g

#####  RULES  ##################################################################

all: $(NAME)

$(NAME): $(LIB) $(OBJ_DIR) $(OBJ) $(INC)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

$(LIB):
	@(cd libft && make CFLAGS="$(CFLAGS)")

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p obj

bonus: $(BONUS)
	@touch .bonus

$(BONUS): $(LIB) $(OBJ_DIR) $(BONUS_OBJ) $(BONUS_INC)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIB) -o $@

clean:
	rm -rf $(OBJ_DIR) ./debug/ .bonus

fclean: clean
	@rm -rf $(NAME) $(BONUS)
	@rm -rf bin

re: fclean all

reb: fclean bonus

#  DEBUG

debug: CFLAGS := $(CFLAGS) $(DEBUG_FLAGS)
debug: clean $(DEBUG)

$(DEBUG): $(LIB) $(OBJ_DIR) $(OBJ) $(INC)
	@mkdir -p debug
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@
	@make clean

debugb: CFLAGS := $(CFLAGS) $(DEBUG_FLAGS)
debugb: clean $(DEBUG_BONUS)

$(DEBUG_BONUS): $(LIB) $(OBJ_DIR) $(BONUS_OBJ) $(BONUS_INC)
	@mkdir -p debug
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIB) -o $@
	@make clean

.PHONY: all clean fclean phony bonus re reb debug debugb
