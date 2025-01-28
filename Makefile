#####  FILES  ##################################################################

NAME := ./bin/pipex

SRC_DIR := ./src/
SRC :=	arg_split.c		get_av.c		get_env_path.c	\
		main.c			pipex.c			open_files.c	\
		error.c			exec_commands.c
SRC := $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR := ./obj/
OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

INC := ./inc/pipex.h

LIB := libft/libft.a

#  BONUS

BONUS := ./bin/pipex_bonus

BONUS_SRC := arg_split.c	get_av.c	get_env_path.c		\
			 main_bonus.c	pipex.c	open_files.c	\
			 error.c		exec_commands.c
BONUS_SRC := $(addprefix $(SRC_DIR), $(BONUS_SRC))

BONUS_OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(BONUS_SRC))

BONUS_INC := ./inc/pipex_bonus.h

#####  COMPILERS  ##############################################################

CC := cc

CFLAGS := -Wall -Wextra -Werror

FSAN_FLAGS := -fsanitize=address

VLGR_FLAGS := --leak-check=full --track-fds=yes

#####  RULES  ##################################################################

all: $(NAME)

lol:
	@echo $(BONUS)
	@echo $(BONUS_SRC)
	@echo $(BONUS_OBJ)
	@echo $(BONUS_INC)

$(NAME): $(LIB) $(OBJ_DIR) $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

$(LIB): phony
	@(cd libft && make CFLAGS="$(CFLAGS)")

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p obj

bonus: $(BONUS)
	@touch .bonus

$(BONUS): $(LIB) $(OBJ_DIR) $(BONUS_OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIB) -o $@

clean:
	rm -rf $(OBJ_DIR) .bonus
	@(cd libft && make clean)

fclean: clean
	rm -rf $(NAME) $(BONUS)
	@(cd libft && make fclean)

re: fclean all

reb: fclean bonus

#  DEBUG

debug: CFLAGS := $(CFLAGS) -g
debug: all

debugb: CFLAGS := $(CFLAGS) -g
debugb: bonus

valgrind: CFLAGS := $(CFLAGS) -g
valgrind: all
	@valgrind $(VLGR_FLAGS) $(NAME) $(ARGS)

fsan: CFLAGS := $(CFLAGS) -g $(FSAN_FLAGS)
fsan: all phony
	$(NAME) $(ARGS)

.PHONY: all clean fclean re phony valgrind fsan bonus
