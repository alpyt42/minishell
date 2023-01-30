/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:57:31 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/30 21:26:56 by ale-cont         ###   ########.fr       */
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

#define FD_READ 0
#define FD_WRITE 1

typedef struct	s_shell
{
	
	char **lign;


	
}	t_shell;

typedef struct s_data
{
	t_list	*nodes;
	t_list	*dico;
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
char	*getuser_prompt(char **env);
void	display_error(char *strerr, char *error);
void	init_dico(t_data *data, char **envp);
char	*search_dico(char *search, t_data *data);

#endif