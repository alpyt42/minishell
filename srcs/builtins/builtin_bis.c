/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:32 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/27 14:33:25 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_node *n)
{
	int			i;
	const char	*built[9];

	i = -1;
	built[0] = "cd";
	built[1] = "export";
	built[2] = "exit";
	built[3] = "unset";
	built[4] = "echo";
	built[5] = "env";
	built[6] = "pwd";
	built[7] = NULL;
	if (!n->all_cmd || n->all_path)
		return (-1);
	while (built[++i])
		if (ft_strncmp(built[i], *n->all_cmd, ft_strlen(*n->all_cmd)) == 0
			&& ft_strlen(*n->all_cmd) == ft_strlen(built[i]))
			return (i);
	return (-1);
}

int	built_env(t_data *d, int tri)
{
	char	**env;
	char	**tab;

	env = d->env;
	if (!env)
		return (0);
	if (!tri)
	{
		(void)tab;
		display_arr(env, "", 1);
	}
	else if (tri)
	{
		tab = sort_arr(env);
		display_arr(tab, "declare -x ", 0);
		ft_free_arr(tab);
	}
	return (0);
}

static int	error_built(char *cmd, char *fct, int *check)
{
	if (cmd && cmd[0] && cmd[0] != '=')
		return (1);
	*check = 0;
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strchars_i(cmd, "()") != -1)
		ft_dprintf(2, "minishell: syntax error near unexpected token '%c'\n",
			cmd[ft_strchars_i(cmd, "()")]);
	else if ((ft_strchars_i(cmd, "-") != -1 && cmd[0] == '-' && !cmd[1])
		|| ft_strchars_i(cmd, "=") != -1)
	{
		ft_dprintf(2, "minishell: %s: '%s': not a valid identifier\n",
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

int	built_export(t_data *data, t_node *n, int i, char **tmp)
{
	char	*var_glob;
	int		check;

	if (!n->all_cmd)
		return (0);
	if (n->all_cmd[0] && !n->all_cmd[1])
		return (built_env(data, 1));
	while (n->all_cmd[++i])
	{
		check = 1;
		if (ft_strchars_i(n->all_cmd[i], "()=[]") != -1)
			error_built(n->all_cmd[i], "export", &check);
		tmp = mini_split(n->all_cmd[i], -1, 0, 0);
		rm_space(tmp);
		if (tmp && tmp[0] && check)
		{
			if (search_dico(tmp[0], data) && !ft_strlen(tmp[1]))
				return (ft_free_arr(tmp), 0);
			var_glob = ft_strjoin(tmp[0], "=");
			set_env_vars(data, var_glob, tmp[1]);
			free(var_glob);
		}
		ft_free_arr(tmp);
	}
	return (0);
}

int	built_unset(t_data *data, t_node *n)
{
	char	**cmds;
	int		i;
	int		pos;

	cmds = n->all_cmd;
	pos = 0;
	if (!cmds || !cmds[0] || !cmds[1])
		return (0);
	i = 0;
	while (cmds[++i])
	{
		if (ft_strchars_i(cmds[i], "()-=") != -1)
			return (error_built(cmds[i], "unset", 0));
		pos = pos_in_arr(data->env, cmds[i], '=');
		if (search_dico(cmds[i], data) && pos != -1)
			data->env = ft_replace_in_matrix(data->env, NULL, pos, -1);
	}
	return (0);
}
