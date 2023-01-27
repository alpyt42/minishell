/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:29:54 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/26 19:35:43 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_user_name(char **env)
{
	char	*prompt;
	char	**user_name;

	user_name = NULL;
	exec_cmd_path(user_name, "/usr/bin/whoami", "whoami", env);
	if (!user_name)
		user_name[0] = "unknown";
	prompt = ft_strjoin(user_name[0], "@");
	prompt = ft_strjoin(prompt, "minishell");
	return (prompt);
}

// static char	*get_current_path(char **env)
// {
	
// }


char	*getuser_prompt(char **env)
{
	char	*user_name;
	// char	*path_pwd;

	user_name = get_user_name(env);
	// path_pwd = get_current_path(env);
	return (user_name);
}