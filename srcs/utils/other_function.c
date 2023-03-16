/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:45:23 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/16 18:33:30 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strchars_i(const char *s, char *set)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	pos_in_arr(char **arr, char *to_find, char set)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(to_find);
	while (arr[++i])
	{
		if (!ft_strncmp(arr[i], to_find, len)
			&& arr[i][len] && arr[i][len] == set)
			return (i);
	}
	return (-1);
}

void	display_arr(char **arr, char *info)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
	{
		printf("%s", info);
		printf("%s\n", arr[i]);
	}
}

void	display_cmd(t_list *cmds)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (cmds)
	{
		i = -1;
		while (((t_node *)cmds->content)->all_cmd[++i])
			dprintf(1, "node n.%d cmds[%d] : %s\n", \
				j, i, ((t_node *)cmds->content)->all_cmd[i]);
		dprintf(1, "node n.%d full_path : %s\n", \
			j, ((t_node *)cmds->content)->all_path);
		dprintf(1, "node n.%d infile : %d\n", \
			j, ((t_node *)cmds->content)->infile);
		dprintf(1, "node n.%d outfile : %d\n", \
			j, ((t_node *)cmds->content)->outfile);
		j++;
		cmds = cmds->next;
	}
}

char	**mini_split(char *str, int i, int j, int lenone)
{
	int		lentwo;
	char	**res;

	lentwo = 0;
	if (!str)
		return (NULL);
	res = ft_calloc(sizeof(char *), 3);
	if (!res)
		return (NULL);
	while (str[lenone] && str[lenone] != '=')
		lenone++;
	if (str[lenone])
		lentwo = ft_strlen(str + lenone);
	res[0] = ft_calloc(sizeof(char), lenone + 1);
	if (lentwo > 0)
		res[1] = ft_calloc(sizeof(char), lentwo);
	if (!res[0] || (!res[1] && lentwo > 0))
		return (NULL);
	while (++i < lenone)
		res[0][i] = str[i];
	i++;
	if (str[lenone])
		while (str[i])
			res[1][j++] = str[i++];
	return (res);
}
