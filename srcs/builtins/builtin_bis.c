/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:32 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/01 15:23:27 by ale-cont         ###   ########.fr       */
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

static int	error_built(char *cmd, char *fct)
{
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strchars_i(cmd, "()") != -1)
		ft_dprintf(2, "minishell: syntax error near unexpected token '%c'\n",
			cmd[ft_strchars_i(cmd, "()")]);
	else if ((ft_strchars_i(cmd, "-") != -1 && cmd[0] == '-' && !cmd[1])
		|| ft_strchars_i(cmd, "=") != -1)
	{
		ft_dprintf(2, "minishell: %s: '%s': : not a valid identifier\n",
			fct, cmd);
		return (1);
	}
	else if (ft_strchars_i(cmd, "-") != -1 && cmd[0] == '-' && cmd[1])
		ft_dprintf(2, "minishell: %s: %c%c: invalid option\n",
			fct, cmd[0], cmd[1]);
	else
		return (0);
	return (2);
}

int	built_export(t_data *data)
{
	char	**cmds;
	char	**tmp;
	char	*var_glob;
	int		i;

	cmds = ((t_node *)data->cmds->content)->all_cmd;
	if (!cmds || !cmds[0] || !cmds[1])
		return (0);
	i = 0;
	while (cmds[++i])
	{
		if (ft_strchars_i(cmds[i], "()-") != -1)
			return (error_built(cmds[i], "export"));
		tmp = mini_split(cmds[i], -1, 0, 0);
		if (tmp[0])
		{
			var_glob = ft_strjoin(tmp[0],"=");
			set_env_vars(data, var_glob, tmp[1]);
			ft_free_arr(tmp);
			free(var_glob);
		}
	}
	return (0);
}

int	built_unset(t_data *data)
{
	char	**cmds;
	int		i;
	int		pos;

	cmds = ((t_node *)data->cmds->content)->all_cmd;
	pos = 0;
	if (!cmds || !cmds[0] || !cmds[1])
		return (0);
	i = 0;
	while (cmds[++i])
	{
		if (ft_strchars_i(cmds[i], "()-=") != -1)
			return (error_built(cmds[i], "unset"));
		pos = pos_in_arr(data->env, cmds[i], '=');
		if (search_dico(cmds[i], data) && pos != -1)
			data->env = ft_replace_in_matrix(data->env, NULL, pos);
		printf("pos : %d\n", pos);
	}
	return (0);
}
