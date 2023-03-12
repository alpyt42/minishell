NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 #-O2 -pipe
# CFLAGS += -fsanitize=address
CFLAGS += -I includes/ -I libft/

LIBFT = libft/libft.a

HEADER = minishell.h
HEADS = srcs/builtins/builtins.h \
		srcs/env/env.h \
		srcs/exec/exec.h \
		srcs/parsing/parsing.h \
		srcs/utils/utils.h

BUILTINS = builtin builtin_bis
ENV = env init get_here_doc
EXEC = exec_cmd mini exec fork_function
MAIN = main prompt signals
PARSING = expand lexing parse_all cmdsplit strim_quotes fill_nodes redirection
UTILS = matrix other_function error struct_test

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

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): lib $(OBJ)
	@echo "\n\033[0;32mCompiling minishell...\033[0m"
	@$(CC) -L $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "\nMinishell is up to date !"

%.o: %.c $(HEADS) $(HEADER) $(LIBFT)
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
