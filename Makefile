  #############
 ##  FILES  ##
#############

NAME := ./bin/pipex

SRC_DIR := ./src/
SRC :=	arg_split.c		av_arr.c		get_env_path.c	\
		main.c			pipe_array.c	pipex.c			\
		error.c			exec_commands.c
SRC := $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR := ./obj/
OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

INC := ./inc/pipex.h

LIB := libft/libft.a

  ################
 ##  COMPILERS ##
################

CC := cc

CFLAGS := -Wall -Wextra -Werror

FSAN_FLAGS := -fsanitize=address

VLGR_FLAGS := --leak-check=full --track-fds=yes

  #############
 ##  RULES  ##
#############

all: $(NAME)

$(NAME): $(LIB) $(OBJ_DIR) $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

$(LIB): phony
	@(cd libft && make CFLAGS="$(CFLAGS)")

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p obj

clean:
	rm -rf $(OBJ)
	@(cd libft && make clean)

fclean: clean
	rm -rf $(NAME)
	@(cd libft && make fclean)

re: fclean all

  ##########
##  DEBUG  ##
 ##########

debug: CFLAGS := $(CFLAGS) -g
debug: all

valgrind: CFLAGS := $(CFLAGS) -g
valgrind: all
	@valgrind $(VLGR_FLAGS) $(NAME) $(ARGS)

fsan: CFLAGS := $(CFLAGS) -g $(FSAN_FLAGS)
fsan: all phony
	$(NAME) $(ARGS)

.PHONY: all clean fclean re phony valgrind fsan
