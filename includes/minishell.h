/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:57:31 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/01 18:19:22 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** libraries
*/
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
#include <sys/types.h>
#include <sys/stat.h>

# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"
# define FD_READ 0
# define FD_WRITE 1

typedef struct s_data
{
	t_list	*nodes;
	t_list	*dico;
	char	**env;
}			t_data;

typedef struct s_node
{
	char	**cmd;
	char 	*path;
	int		infile;
	int		outfile;
}			t_node;

void	exec_cmd_path(char **res, char *path, char *cmd, char **env);
char	**ft_append_tab(char **tab, char *line);
void	display_error(char *strerr, char *error);
void	init_dico(t_data *data, char **envp);
char	*search_dico(char *search, t_data *data);
char	*get_prompt(t_data *data);
void	signal_receive(int sig);

#endif