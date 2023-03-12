/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:57:31 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/07 12:56:09 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>

# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"

typedef struct s_data
{
	t_list	*cmds;
	t_list	*dico;
	char	**env;
	char	**argv;
	int		quit;
	int		n_cmd;
	pid_t	*p_ids;
}			t_data;

typedef struct s_node
{
	char	**all_cmd;
	char	*all_path;
	int		infile;
	int		outfile;
}			t_node;

enum	e_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

# include "../srcs/builtins/builtins.h"
# include "../srcs/env/env.h"
# include "../srcs/exec/exec.h"
# include "../srcs/parsing/parsing.h"
# include "../srcs/utils/utils.h"

char	*get_prompt(t_data *data);
void	signal_receive(int sig);

#endif