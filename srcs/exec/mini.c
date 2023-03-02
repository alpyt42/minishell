/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:03:39 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/02 23:53:26 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

int	mini_process(t_data *data)
{
	t_node	*n;
	int		i;

	n = data->cmds->content;
	i = 0;
	while(data->cmds)
	{
		if (!n->all_cmd)
			return (-1);
		if (data->n_cmd == 1 && is_builtin(n) == 0)
			s_error = built_cd(data);
		else if (data->n_cmd == 1 && is_builtin(n) == 1)
			s_error = built_export(data);
		else if (data->n_cmd == 1 && is_builtin(n) == 2)
			s_error = built_exit(data);
		else if (data->n_cmd == 1 && is_builtin(n) == 3)
			s_error = built_unset(data);
		else if (data->n_cmd > 1 && is_builtin(n) <= 3)
			i++;
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
