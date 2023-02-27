NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 #-O2 -pipe
# CFLAGS += -fsanitize=address
CFLAGS += -I includes/ -I libft/

LIBFT = libft/libft.a

HEADER = minishell.h

BUILTINS = builtin
ENV = env init get_here_doc get_file
EXEC = exec_cmd mini
MAIN = main
PARSING = token expand lexing parse_all cmdsplit strim_quotes fill_nodes
TOOLS = error
UTILS = matrix other_function
PROMPT = prompt
SIGNALS = signals

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
	  $(addsuffix .c, $(addprefix srcs/signals/, $(SIGNALS))) \

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): lib $(OBJ)
	@echo "\n\033[0;32mCompiling minishell...\033[0m"
	@$(CC) -L $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "\nMinishell is up to date !"

%.o: %.c $(HEADER) $(LIBFT)
	@echo "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} -I $(CFLAGS) -c $< -o $@

lib :
	$(MAKE) -C ./libft

leak: all
	@$(LEAKS)./$(NAME)

clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -C libft/
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@rm -f includes/$(HEADER).gch
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@rm -f includes/$(HEADER).gch
	@echo "\033[0m"

re: fclean all

.PHONY: clean fclean re test norm
