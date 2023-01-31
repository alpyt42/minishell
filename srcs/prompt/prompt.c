/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:29:54 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/31 13:23:01 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_user_name(t_data *data)
{
	char	*user_name;

	user_name = search_dico("USER", data);
	if (!user_name)
		user_name = "unknown";
	user_name = ft_strjoin(user_name, "@minishell:");
	return (user_name);
}

// char	*last_word(char *str, char *set)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen(str);
// }

static char	*get_path(t_data *data)
{
	char	*pwd;
	char	*pwd_mini;
	char	*path;

	pwd = search_dico("PWD", data);
	pwd_mini = ft_strstr(pwd, search_dico("USER", data));
	if (pwd_mini)
	{
		pwd_mini = ft_strstr(pwd_mini, "/");
		if(!pwd_mini)
			path = "~";
		else
			path = ft_strjoin("~", pwd_mini);
	}
	else
		path = pwd;
	return (path);
}


char	*get_prompt(t_data *data)
{
	char	*prompt;
	char	*user_name;
	char	*path;
	char	*tmp;

	user_name = get_user_name(data);
	path = get_path(data);
	tmp = ft_strjoin(user_name, path);
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	free(path);
	free(user_name);
	return (prompt);
}
