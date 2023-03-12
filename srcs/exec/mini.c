/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:03:39 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/13 00:05:05 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int	s_error;

int	exec_builtin(t_data *d, t_node *n)
{
	// dprintf(2,"exec_builtins for %s\n", *n->all_cmd);
	if (is_builtin(n) == -1)
		return (0);
	if (is_builtin(n) == 0)
		s_error = built_cd(d, n);
	else if (is_builtin(n) == 1)
		s_error = built_export(d, n);
	else if (is_builtin(n) == 2)
		s_error = built_exit(d, n);
	else if (is_builtin(n) == 3)
		s_error = built_unset(d, n);
	else if (is_builtin(n) == 4)
		s_error = built_echo(n);
	else if (is_builtin(n) == 5)
		s_error = built_env(d, 0);
	else if (is_builtin(n) == 6)
		s_error = built_pwd();
	return (s_error);
}

int	mini_process(t_data *data, t_list *cmds)
{
	t_node	*n;

	n = data->cmds->content;
	// printf("DISPLAY CMDS : \n");
	// display_cmd(data->cmds);
	// printf("data->n_cmd : %d\n", data->n_cmd);
	// printf("START MINI PROCESS\n----------------\n");
	if (data->n_cmd == 1 && is_builtin(n) >= 0)
		return(exec_builtin(data, n));
	while(cmds)
	{
		if (!n->all_cmd)
			return (-1);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec(data, cmds);
		}
		cmds = cmds->next;
	}
	return (s_error);
}

static void	get_error(t_data *d)
{
	if (!d->quit && s_error == 13)
		s_error = 0;
	if (s_error > 255)
		s_error = s_error / 255;
}

int	launch_mini(t_data *data, char *cmd)
{
	if (!cmd)
	{
		ft_dprintf(1, "exit\n");
		ft_free_mini(data);
		return (0);
	}
	if (ft_strlen(cmd) <= 0)
		return (1);
	if (cmd[0] != '\0')
		add_history(cmd);
	if (check_pars(cmd, data))
		return (1);
	// display_cmd(data->cmds);
	data->n_cmd = ft_lstsize(data->cmds);
	if (data->n_cmd > 0 && data->exe)
		mini_process(data, data->cmds);
	while (data->n_cmd-- > 0)
		waitpid(-1, &s_error, 0);
	get_error(data);
	// printf("----------------\nEND MINI_PROCESS\n");
	// display_cmd(data->cmds);
	ft_lstclear(&data->dico, ft_free_dico);
	ft_lstclear(&data->cmds, ft_free_node);
	init_dico(data);
	return (1);
}
