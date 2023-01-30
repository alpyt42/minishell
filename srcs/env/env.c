/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:40:02 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/27 17:01:47 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_dico(t_data *data, char **envp)
{
	// t_list	*dico; 
	int		i;
	char	**cmd;
	
	i = 0;
	cmd = ft_split(envp[i++], '=');
	
	data->dico = ft_lstnew(cmd);
	printf("%s\n", (char *)data->dico->content);
	
	// while(envp[i])
	// {
	// 	cmd = ft_split(envp[i], '=');
	// 	printf("<<%s>>\n", cmd[1]);
	// 	ft_lstadd_back(&data->dico, ft_lstnew(cmd));
	// 	i++;
	// }
	
}