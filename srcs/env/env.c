/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:40:02 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/30 19:38:30 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_dico(t_data *data, char **envp)
{
	int		i;
	char	**cmd;
	
	i = 0;
	while(envp[i])
	{
		cmd = ft_split(envp[i], '=');
		ft_lstadd_back(&data->dico, ft_lstnew(cmd));
		i++;
	}
}

char *search_dico(char *search, t_data *data)
{
	char	**cmd;
	while (data->dico)
	{
		cmd = data->dico->content;
		if (!(ft_strncmp(cmd[0], search, 200)))
		{
			return(cmd[1]);
		}
		data->dico = data->dico->next;
	}
	return (NULL);
}