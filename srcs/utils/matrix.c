/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:24:09 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/08 14:50:32 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

char	**ft_append_tab(char **tab, char *line)
{
	char	**res;
	int		len;
	int		i;

	i = -1;
	res = NULL;
	if (!line)
		return (tab);
	len = len_tab(tab);
	res = malloc(sizeof(char *) * (len + 2));
	res[len + 1] = NULL;
	if (!res)
		return (tab);
	while (++i < len)
	{
		res[i] = ft_strdup(tab[i]);
		if (!res[i])
		{
			ft_free_arr(tab);
			ft_free_arr(res);
		}
	}
	res[i] = ft_strdup(line);
	ft_free_arr(tab);
	return (res);
}

char **ft_replace_in_matrix(char **matrix, char **insert, int n)
{
	char **temp;
	
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = -1;
	if (!matrix || n < 0 || n >= len_tab(matrix))
		return (NULL);
	temp = ft_calloc((len_tab(matrix) + len_tab(insert)), sizeof(char*));
	int test = len_tab(matrix);
	(void) test;
	if (!temp)
		return (NULL);
	while (temp && matrix[++i])
	{
		if (i != n)
			temp[++j] = ft_strdup(matrix[i]);
		else
		{
			while (insert && insert[++k])
				temp[++j] = ft_strdup(insert[k]);
		}
	}
	ft_free_arr(matrix);
	matrix = temp;
	return (matrix);
}

char	**sort_arr(char **arr)
{
	char	**res;
	char	*tmp;
	int		len;
	int		i;
	int		j;

	i = -1;
	len = ft_arrlen(arr);
	if (!len)
		return (NULL);
	res = ft_calloc(sizeof(char *), len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, arr, len);
	while (++i < len - 1)
	{
		j = i;
		while (++j < len)
			if (ft_strncmp(res[i], res[j], INT_MAX) > 0)
			{
				tmp = res[i];
				res[i] = res[j];
				res[j] = tmp;
			}
	}
	return (res);
}
