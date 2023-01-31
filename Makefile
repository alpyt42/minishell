NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/
CDEBUG = #-fsanitize=address

LIBFT = libft/libft.a

HEADER = minishell.h

BUILTINS = builtin
ENV = env
EXEC = exec
MAIN = main
PARSING = token
TOOLS = error
UTILS = matrix other_function
PROMPT = prompt
UNAME = $(shell uname -s)

ifeq ($(UNAME), Linux)
	#Properties for Linux
	LEAKS = valgrind --leak-check=full --track-fds=yes --trace-children=yes -s -q 
endif

SRC = $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \
	  $(addsuffix .c, $(addprefix srcs/utils/, $(UTILS))) \
	  $(addsuffix .c, $(addprefix srcs/prompt/, $(PROMPT))) \

OBJ = $(SRC:c=o)

all: lib $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@echo "\033[0;32mCompiling minishell...\033[0m"
	@$(CC) -L $(CFLAGS) -o $(NAME) $(OBJ) -lreadline $(LIBFT)
	@echo "\nDone !"

%.o: %.c $(HEADER) $(LIBFT)
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include $(CFLAGS) $(CDEBUG) -c $< -o $@

lib :
	$(MAKE) -C ./libft

leak: all
	@$(LEAKS)./$(NAME)

clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -C libft/
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: clean fclean re test norm
