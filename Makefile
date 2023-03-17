NAME = minishell

CC = gcc

HEADER = ./includes/
HEADS = ./srcs/builtins/builtins.h \
		./srcs/env/env.h \
		./srcs/parsing/parsing.h \
		./srcs/utils/utils.h \
		./includes/minishell.h \
		
		
CFLAGS = -Wall -Wextra -Werror -g3 -I $(HEADER)
# CDEBUG = -fsanitize=address

LIBFT = libft/libft.a
		

BUILTINS = builtin builtin_bis
ENV = env init get_here_doc
EXEC = exec_cmd mini exec fork_function
MAIN = main prompt signals
PARSING = expand lexing parse_all cmdsplit strim_quotes fill_nodes redirection
UTILS = matrix other_function error

UNAME = $(shell uname -s)

ifeq ($(UNAME), Linux)
	#Properties for Linux
	LEAKS = valgrind --leak-check=full --track-fds=yes --trace-children=yes -s -q 
endif

SRC =	$(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
		$(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
		$(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
		$(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
		$(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
		$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS)))

OBJ = $(SRC:.c=.o)

all: lib $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;32mCompiling minishell...\033[0m"
	@$(CC) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $(CFLAGS) $(CDEBUG) $(OBJ) $(LIBFT) -lreadline -o $@
	@echo "\nMinishell is up to date !"

%.o: %.c $(LIBFT) $(HEADS)
	$(CC) -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include $(CFLAGS) $(CDEBUG) -c $< -o $@

lib :
	$(MAKE) -C ./libft

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

.PHONY: all clean fclean re lib
