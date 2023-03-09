/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:03:39 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/09 16:19:17 by ale-cont         ###   ########.fr       */
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

int	mini_process(t_data *data, t_list *cmds)
{
	t_node	*n;

	data->n_cmd = ft_lstsize(data->cmds);
	n = data->cmds->content;
	printf("DISPLAY CMDS : \n");
	display_cmd(data->cmds);
	printf("data->n_cmd : %d\n----------------\n", data->n_cmd);
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
	printf("START MINI PROCESS\n");
	display_cmd(data->cmds);
	mini_process(data, data->cmds);
	while (data->n_cmd-- > 0)
		waitpid(-1, &s_error, 0);
	printf("END MINI_PROCESS\n");
	display_cmd(data->cmds);
	ft_lstclear(&data->dico, ft_free_dico);
	ft_lstclear(&data->cmds, ft_free_node);
	init_dico(data);
	return (1);
}
