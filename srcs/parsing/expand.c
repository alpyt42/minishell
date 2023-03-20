/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:11:15 by amontalb          #+#    #+#             */
/*   Updated: 2023/03/20 16:59:28 by amontalb         ###   ########.fr       */
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
	{
		before = strdup(path);
		path = ft_strjoin(before, &cmd[i]);
		free(before);
	}
	free (cmd);
	return (path);
}

char	*expand_path(char *temp, t_data *data, int *tab)
{
	char	*cmd;

	cmd = ft_strdup(temp);
	while (cmd && cmd[tab[0]])
	{
		tab[1] = (tab[1] + (!tab[2] && cmd[tab[0]] == '\'')) % 2;
		tab[2] = (tab[2] + (!tab[1] && cmd[tab[0]] == '\"')) % 2;
		if (!tab[1] && !tab[2] && cmd[tab[0]] == '~'
			&& (tab[0] == 0 || !cmd[tab[0] - 1]))
		{
			if ((cmd[tab[0] + 1] && cmd[tab[0] + 1] != ' '))
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

char	*sub_var2(cmd, before, i)
{
	char	*var;
	char	*temp;
	
}
char	*sub_var(char *cmd, t_data *data, int i)
{
	char	*before;
	char	*path;
	char	*var;
	char	*temp;

	temp = ft_substr(cmd, i + 1, ft_strchars_i(&cmd[i + 1], "|$?~%^{}: \"\'"));
	before = ft_substr(cmd, 0, i);
	var = search_dico(temp, data);
	free(temp);
	if (!var && cmd[i + 1] && (cmd[i + 1] == '$' || cmd[i + 1] == '?'))
	{
		if (cmd[i + 1] == '$')
			var = ft_itoa(data->p_ids);
		else
			var = ft_itoa(g_error);
		temp = ft_strjoin(before, var);
		path = ft_strjoin(before, &cmd[i + 2]);
		free (temp);
		free(before);
		free(var);
		free(cmd);
		return (path);
	}
	else
		path = ft_strjoin(before, var);
	free(before);
	if (ft_strchars_i(&cmd[i + 1], "|$?~%^${}: \"") != -1)
	{
		temp = ft_strdup(path);
		free (path);
		path = ft_strjoin(temp, &cmd[i
				+ 1 + ft_strchars_i(&cmd[i + 1], "|$?~%^${}: \"")]);
		free(temp);
	}
	free(cmd);
	return (path);
}

char	*expand_vars(char *temp, t_data *data, int *tab)
{
	char	*cmd;

	cmd = ft_strdup(temp);
	while (cmd && cmd[tab[2]])
	{
		tab[0] = (tab[0] + (!tab[1] && cmd[tab[2]] == '\'')) % 2;
		tab[1] = (tab[1] + (!tab[0] && cmd[tab[2]] == '\"')) % 2;
		if (!tab[0] && cmd[tab[2] + 1] && cmd[tab[2]] == '$' && cmd[tab[2] + 1]
			&& ((ft_strchars_i(&cmd[tab[2] + 1], "|~$%^{}: \"") && tab[1])
				|| (ft_strchars_i(&cmd[tab[2] + 1], "~$%^{}: ") && !tab[1])
				|| (cmd[tab[2] + 1] == '$')))
		{
			cmd = sub_var(cmd, data, tab[2]);
			tab[2] = tab[2] * tab[3] - (1 * tab[3])
				+ ft_strchars_i(&cmd[tab[2]], "|?~%$^{}: \"");
			if (ft_strchars_i(&cmd[tab[2] + 1], "|?~%$^{}: \"") && tab[2] < 0)
				tab[2]++;
			tab[3] = 1;
		}
		else
			tab[2]++;
	}
	return (cmd);
}

char	*expand_all2(char *cmd, t_data *data)
{
	int		tab[4];
	int		tob[4];
	char	*temp;
	char	*temp2;

	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = ft_strlen(search_dico("HOME", data));
	tob[3] = 0;
	tob[2] = 0;
	tob[0] = 0;
	tob[1] = 0;
	temp = expand_vars(cmd, data, tob);
	temp2 = expand_path(temp, data, tab);
	free(temp);
	return (temp2);
}
