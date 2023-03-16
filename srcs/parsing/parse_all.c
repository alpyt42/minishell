/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:43:12 by amontalb          #+#    #+#             */
/*   Updated: 2023/03/16 01:13:18 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern int s_error;

static char **split_all(char **cmd)
{
	char **cmdsplit;
	int i;

	i = -1;
	while (cmd[++i])
	{
		cmdsplit = ft_cmdsplit(cmd[i], "<|>");
		if (!cmdsplit)
			return (cmd);
		cmd = ft_replace_in_matrix(cmd, cmdsplit, i);
		// ft_free_matrix(cmdsplit);
	}
	return (cmd);
}

static int check_empty_node(char *cmd)
{
	int i;
	int empty;

	empty = 0;
	i = -1;
	if (ft_strchars_i(cmd, "|") != -1)
	{
		while (cmd[++i])
		{
			empty = 0;
			while (cmd[i] && cmd[i] != '|')
			{
				if (cmd[i] != ' ')
					empty++;
				i++;
			}
			if (!empty)
				return (1);
		}
	}
	return (0);
}

static int	check_chev(char **cmd, t_data *d)
{
	int		count;
	char	*ch;
	int		i;
	int		j;

	i = -1;
	while (cmd[++i])
	{
		count = 1;
		j = i + 1;
		ch = NULL;
		if (cmd[i][0] == '<' || cmd[i][0] == '>')
			ch = cmd[i];
		if (ch && (ch[0] == '>' || ch[0] == '<'))
			while (cmd[j] && cmd[j][0] && cmd[j][0] == ch[0])
			{
				count++;
				j++;
			}
		if ((count > 2 && cmd[i + 1][0] && cmd[i + 2][0]))
			return (symbol_errors(ch, 2, &d->exe));
		else if ((!cmd[j] && cmd[j - 1][0] == ch[0]))
			return (symbol_errors("", 2, &d->exe));
	}
	return (0);
}

static int check_error(char *cmd)
{
	int	i;
	int	simple_q;
	int	double_q;

	i = 0;
	simple_q = 0;
	double_q = 0;
	while (cmd[i])
	{
		simple_q = (simple_q + (!double_q && cmd[i] == '\'')) % 2;
		double_q = (double_q + (!simple_q && cmd[i] == '\"')) % 2;
		if (!simple_q && !double_q && (cmd[i] == ';' || cmd[i] == '\\' 
			|| (cmd[i] == '|' && cmd[i + 1] && cmd[i + 1] == '|') 
			|| (cmd[i] == '&' && cmd[i + 1] && cmd[i + 1] == '&') 
			|| (cmd[i] == '|' && !cmd[i + 1])))
			return (1);
		i++;
	}
	if (simple_q == 1 || double_q == 1)
		return (1);
	return (0);
}

int	check_pars(char *cmd, t_data *data)
{
	char	**parsed;

	parsed = NULL;
	if (check_error(cmd))
	{
		ft_dprintf(1, "ERROR ARG -> cmd1 | cmd2\n");
		data->exe = 0;
		s_error = 0;
		return (1);
	}
	if (check_empty_node(cmd))
	{
		symbol_errors("|", 2, &data->exe);
		return (1);
	}
	parsed = cmdlexing(cmd);
	parsed = split_all(parsed);
	if (check_chev(parsed, data))
		return (ft_free_arr(parsed), 0);
	data->cmds = fill_nodes(parsed, data);
	return (0);
}