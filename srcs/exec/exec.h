/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:16:59 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/14 13:14:00 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../includes/minishell.h"

void	exec_cmd_path(char ***res, char *path, char *cmd, char **env);
int		errors(char *strerr, char *error, int n);
int		mini_process(t_data *data, t_list *cmds);
void	*exec(t_data *data, t_list *cmd);
void	*fork_fct(t_data *d, t_list *cmd, int fd[2]);
int		exec_builtin(t_data *d, t_node *n);
int		launch_mini(t_data *data, char *cmd);
void	*redir_dup(t_list *cmd, int fd[2]);

#endif