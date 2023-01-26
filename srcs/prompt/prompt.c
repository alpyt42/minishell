/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:29:54 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/26 16:00:45 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_user_name(char **env)
{
	
}

char	*get_current_path(char **env)
{
	
}


char	*getuser_prompt(char **env)
{
	char	*user_name;
	char	*path_pwd;

	user_name = get_user_name(env);
	path_pwd = get_current_path(env);
	
}