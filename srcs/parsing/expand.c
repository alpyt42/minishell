/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:11:15 by amontalb          #+#    #+#             */
/*   Updated: 2023/03/17 15:19:42 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern int	g_error;

char	*sub_path(char *cmd, t_data *data, int i)
{
	char	*before;
	char	*path;

	before = NULL;
	if (i != 0)
	{
		before = ft_substr(cmd, 0, i);
		path = ft_strjoin(before, search_dico("HOME", data));
		free(before);
	}
	else
		path = ft_strdup(search_dico("HOME", data));
	i++;
	if (cmd[i])
		path = ft_strjoin(path, &cmd[i]);
	return (path);
}

char	*expand_path(char *cmd, t_data *data, int *tab)
{
	while (cmd[tab[0]])
	{
		tab[1] = (tab[1] + (!tab[2] && cmd[tab[0]] == '\'')) % 2;
		tab[2] = (tab[2] + (!tab[1] && cmd[tab[0]] == '\"')) % 2;
		if (!tab[1] && !tab[2] && cmd[tab[0]] == '~'
			&& (tab[0] == 0 || !cmd[tab[0] - 1]))
		{
			if ((cmd[tab[0] + 1] && cmd[tab[0] + 1] != ' ')
				|| (cmd[tab[0] - 1] && cmd[tab[0] - 1] == '~'))
				tab[0]++;
			else
			{
				cmd = sub_path(cmd, data, tab[0]);
				tab[0] += tab[3];
			}
		}
		else
			tab[0]++;
	}
	return (cmd);
}

char	*sub_var(char *cmd, t_data *data, int i)
{
	char	*before;
	char	*path;
	char	*var;

	before = ft_substr(cmd, 0, i);
	var = search_dico(ft_substr(cmd, i + 1,
				ft_strchars_i(&cmd[i + 1], "|$?~%^{}: \"\'")), data);
	if (before)
		path = ft_strdup(before);
	if (!var && cmd[i + 1] && cmd[i + 1] == '$')
	{
		var = ft_itoa(data->p_ids);
		path = ft_strjoin(path, var);
		path = ft_strjoin(path, &cmd[i + 2]);
		free(var);
		free(before);
		return (path);
	}
	if (!var && cmd[i + 1] && cmd[i + 1] == '?')
	{
		var = ft_itoa(g_error);
		path = ft_strjoin(path, var);
		path = ft_strjoin(path, &cmd[i + 2]);
		free(var);
		free(before);
		return (path);
	}
	else
		path = ft_strjoin(before, var);
	if (ft_strchars_i(&cmd[i + 1], "|$?~%^${}: \"") != -1)
		path = ft_strjoin(path, &cmd[i
				+ ft_strchars_i(&cmd[i + 1], "|$?~%^${}: \"")]);
	return (path);
}

char	*expand_vars(char *cmd, t_data *data)
{
	int	simple_q;
	int	double_q;
	int	i;
	int	k;

	k = 0;
	i = 0;
	simple_q = 0;
	double_q = 0;
	while (cmd[i])
	{
		simple_q = (simple_q + (!double_q && cmd[i] == '\'')) % 2;
		double_q = (double_q + (!simple_q && cmd[i] == '\"')) % 2;
		if (!simple_q && cmd[i] == '$' && cmd[i + 1]
			&& ((ft_strchars_i(&cmd[i + 1], "|~$%^{}: \"") && double_q)
				|| (ft_strchars_i(&cmd[i + 1], "~$%^{}: ") && !double_q)
				|| (cmd[i + 1] == '$')))
		{
			cmd = sub_var(cmd, data, i);
			i = i * k - (1 * k) + ft_strchars_i(&cmd[i], "|?~%$^{}: \"");
			if (ft_strchars_i(&cmd[i], "|?~%$^{}: \"") && i < 0)
				i++;
			k = 1;
		}
		else
			i++;
	}
	return (cmd);
}

char	*expand_all2(char *cmd, t_data *data)
{
	int	tab[4];

	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = ft_strlen(search_dico("HOME", data));
	cmd = expand_vars(cmd, data);
	cmd = expand_path(cmd, data, tab);
	return (cmd);
}
