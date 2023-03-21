/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:24:09 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/21 13:11:23 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

char	**ft_append_tab(char **tab, char *line)
{
	char	**res;
	int		len;
	int		i;

	i = -1;
	res = NULL;
	if (!line)
		return (tab);
	len = ft_arrlen(tab);
	res = ft_calloc(sizeof(char *), (len + 2));
	if (!res)
		return (tab);
	while (++i < len)
	{
		res[i] = ft_strdup(tab[i]);
		if (!res[i])
		{
			ft_free_arr(tab);
			ft_free_arr(res);
			return(NULL);
		}
	}
	res[i] = ft_strdup(line);
	ft_free_arr(tab);
	return (res);
}

char	**ft_replace_in_matrix(char **matrix, char **insert, int n, int i)
{
	char	**temp;
	int		j;
	int		k;

	j = -1;
	k = -1;
	if (!matrix || n < 0 || n >= ft_arrlen(matrix))
		return (NULL);
	temp = ft_calloc((ft_arrlen(matrix) + ft_arrlen(insert)), sizeof(char *));
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
	int		i;
	int		j;

	i = -1;
	if (!arr)
		return (NULL);
	res = ft_arrdup(arr);
	if (!res)
		return (NULL);
	while (arr[++i])
	{
		j = i;
		while (arr[++j])
		{
			if (ft_strncmp(res[i], res[j], INT_MAX) > 0)
			{
				tmp = res[i];
				res[i] = res[j];
				res[j] = tmp;
			}
		}
	}
	return (res);
}

static void	mod_space(char *str, int i, int j, int n)
{
	int	k;

	while (i < n)
	{
		if (str[i] == ' ')
		{
			j = i + 1;
			while (j < n && str[j] == ' ')
				j++;
			if (j - i > 1)
			{
				k = j - 1;
				while (++k < n)
					str[k - (j - i - 1)] = str[k];
				str[k - (j - i - 1)] = '\0';
				n -= j - i - 1;
			}
			else
				i++;
		}
		else
			i++;
	}
	if (n > 0 && str[n - 1] == ' ')
		str[n - 1] = '\0';
}

void	rm_space(char **str)
{
	int	len;

	if (!str)
		return ;
	len = ft_arrlen(str);
	if (len > 2)
	{
		g_error = 1;
		ft_dprintf(2, "mini: export: `%s': not a valid identifier",
			str[len - 1]);
	}
	if (len == 2)
		mod_space(str[1], 0, 0, ft_strlen(str[1]));
}
