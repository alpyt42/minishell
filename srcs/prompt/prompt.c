/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:29:54 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/31 15:24:14 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_user_name(t_data *data)
{
	char	*user_name;
	char	*tmp;
	char	*tmp2;

	tmp = search_dico("USER", data);
	if (!tmp)
		tmp = "unknown";
	tmp = ft_strjoin(tmp, "@minishell:");
	tmp2 = ft_strjoin(GREEN, tmp);
	user_name = ft_strjoin(tmp2, DEFAULT);
	free(tmp);
	free(tmp2);
	return (user_name);
}

static char	*get_path(t_data *data)
{
	char	*pwd;
	char	*pwd_mini;
	char	*path;
	char	*tmp;
	char	*tmp2;

	pwd = search_dico("PWD", data);
	pwd_mini = ft_strstr(pwd, search_dico("USER", data));
	if (pwd_mini)
	{
		pwd_mini = ft_strstr(pwd_mini, "/");
		if(!pwd_mini)
			tmp = ft_strdup("~");
		else
			tmp = ft_strjoin("~", pwd_mini);
	}
	else
		tmp = ft_strdup(pwd);
	tmp2 = ft_strjoin(BLUE, tmp);
	path = ft_strjoin(tmp2, DEFAULT);
	free(tmp);
	free(tmp2);
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
