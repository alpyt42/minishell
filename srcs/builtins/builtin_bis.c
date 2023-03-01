/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:32 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/28 18:45:17 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

int	is_builtin(char *cmd)
{
	int			i;
	const char	*built[9];

	i = -1;
	built[0] = "cd";
	built[1] = "export";
	built[2] = "exit";
	built[3] = "unset";
	built[4] = "ls";
	built[5] = "echo";
	built[6] = "env";
	built[7] = "pwd";
	built[8] = NULL;
	if (!cmd)
		return (-1);
	while (built[++i])
		if (ft_strncmp(built[i], cmd, ft_strlen(cmd)) == 0
		&& ft_strlen(cmd) == ft_strlen(built[i]))
			return (i);
	return (-1);
}

int	built_export(t_data *data)
{
	char	**cmds;
	char	**tmp;
	int		i;

	cmds = ((t_node *)data->cmds->content)->all_cmd;
	if (!cmds || !cmds[0] || !cmds[1])
		return (-1);
	i = 0;
	while (cmds[++i])
	{
		tmp = mini_split(cmds[i], 0, 0, 0);
		display_arr(tmp, "export tmp");
		if (tmp)
		{
			set_env_vars(data, tmp[0], tmp[1]);
			ft_free_arr(tmp);
		}
	}
	display_arr(data->env, "export env");
	return (0);
}
