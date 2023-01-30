/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:00:14 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/30 09:24:19 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
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

void	exec_cmd_path(char **res, char *path, char *cmd, char **env);
char	**ft_append_tab(char **tab, char *line);
char	*getuser_prompt(char **env);
void	display_error(char *strerr, char *error);


#endif
