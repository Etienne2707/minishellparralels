NAME = minishell

SRC_DIR = ./src

BIN_DIR = ./bin/

SRC =	$(SRC_DIR)/main.c			\
		$(SRC_DIR)/utils.c			\
		$(SRC_DIR)/token.c			\
		$(SRC_DIR)/split.c		\
		$(SRC_DIR)/utils2.c			\
		$(SRC_DIR)/dollars.c		\
		$(SRC_DIR)/quote.c		\
		$(SRC_DIR)/redirection.c		\
		$(SRC_DIR)/list.c		\
		$(SRC_DIR)/syntax_error.c		\



		



OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)%.o)


LIB_PATH = ./test

LIB = -Llibft 

INCLUDES = ./includes

CFLAGS =-I$(INCLUDES) -g3

all :	$(BIN_DIR) $(NAME)

$(OBJ) :	 $(BIN_DIR)%.o: $(SRC_DIR)/%.c
		@ $(CC) $(CFLAGS) -c $< -o $@

$(NAME) :	$(BIN_DIR) $(OBJ)
			@ $(MAKE) -s -C $(LIB_PATH)
			@ $(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -lreadline
			@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"

$(BIN_DIR) :
		@ mkdir -p $(BIN_DIR)

clean :
		@ $(MAKE) -s clean -C $(LIB_PATH)
		@ rm -f $(OBJ)
		@ rm -rf $(BIN_DIR)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove binary files .. 🧹"

fclean : clean
		@ $(MAKE) -s fclean -C $(LIB_PATH)
		@ rm -f $(NAME)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove executable .. 🗑️"
		
re :
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRecompile .. 🔄"
	@ $(MAKE) -s fclean all

.PHONY: all clean fclean re