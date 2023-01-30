/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:40:02 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/30 21:58:50 by ale-cont         ###   ########.fr       */
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
		ft_lstadd_back(&data->dico, ft_lstnew(cmd)); // cmd ** VS ft_lstnew(cmd) *
		i++;
	}
}

char *search_dico(char *search, t_data *data)
{
	char	**cmd;
	void	*tmp;

	tmp = data->dico;
	while (data->dico)
	{
		cmd = data->dico->content;
		// ft_dprintf(1, "\nsearch : %s && cmd[0] %s\n", search, cmd[0]);
		// ft_dprintf(1, "\n cmd : %d && search %d strcomp %d\n", ft_strlen(cmd[0]), ft_strlen(search), ft_strncmp(cmd[0], search, ft_strlen(search)));
		if (!ft_strncmp(cmd[0], search, ft_strlen(search))\
			&& ft_strlen(cmd[0]) == ft_strlen(search))
		{
			data->dico = tmp;
			return(cmd[1]);
		}
		data->dico = data->dico->next;
	}
	data->dico = tmp;
	return (NULL);
}