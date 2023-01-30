/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:24:09 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/30 19:42:09 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_append_tab(char **tab, char *line)
{
	char	**str;
	int		i;

	i = -1;
	if (!tab)
		return (NULL);
	if (!line)
		return (tab);
	str = (char **)malloc(sizeof(char *) * (ft_arrlen(tab) + 2));
	if (!str)
		return (tab);
	while (++i < ft_arrlen(tab))
		str[i] = ft_strdup(tab[i]);
	str[i] = ft_strdup(line);
	str[++i] = 0;
	ft_free_arr(tab);
	return (str);
}