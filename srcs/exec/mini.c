/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:03:39 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/08 14:45:05 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

int	exec_builtin(t_data *d, t_node *n)
{
	if (is_builtin(n) == -1)
		return (0);
	if (is_builtin(n) == 0)
		s_error = built_cd(d);
	else if (is_builtin(n) == 1)
		s_error = built_export(d);
	else if (is_builtin(n) == 2)
		s_error = built_exit(d);
	else if (is_builtin(n) == 3)
		s_error = built_unset(d);
	else if (is_builtin(n) == 4)
		s_error = built_echo(d);
	else if (is_builtin(n) == 5)
		s_error = built_env(d, 0);
	else if (is_builtin(n) == 6)
		s_error = built_pwd();
	return (s_error);
}

int	mini_process(t_data *data)
{
	t_node	*n;

	n = data->cmds->content;
	while(data->cmds)
	{
		if (!n->all_cmd)
			return (-1);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec(data);
		}
		data->cmds = data->cmds->next;
	}
	return (s_error);
}

int	launch_mini(t_data *data, char *cmd)
{
	(void)data;
	char	*cmd_trim;

	(void)cmd_trim;
	if (!cmd)
	{
		ft_dprintf(1, "exit\n");
		return (0);
	}
	if (cmd[0] != '\0')
		add_history(cmd);
	// --------> ADD MINI PROCESS HERE <-------
	return (1);
}
