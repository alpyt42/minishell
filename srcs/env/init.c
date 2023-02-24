/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:33:30 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/24 17:02:25 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

static void init_shlvl(t_data *data)
{
	char *shlvl;

	shlvl = NULL;
	shlvl = find_in_arr(data->env, "SHLVL=");
	if (!shlvl)
		set_env_vars(data, "SHLVL=", "1");
	else if ((ft_atoi(shlvl) + 1) < 0)
		set_env_vars(data, "SHLVL=", "0");
	else
	{
		shlvl = ft_itoa((ft_atoi(shlvl) + 1));
		set_env_vars(data, "SHLVL=", shlvl);
		free(shlvl);
	}
}

static void init_vars(t_data *data)
{
	char *pwd;
	char *underscore;
	char *path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("no_path_found");
	set_env_vars(data, "PWD=", pwd);
	init_shlvl(data);
	free(pwd);
	path = find_in_arr(data->env, "PATH=");
	if (!path)
		set_env_vars(data, "PATH=",
					 "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	underscore = find_in_arr(data->env, "_=");
	if (!underscore)
		set_env_vars(data, "_=", data->argv[0]);
}

void init_data(t_data *data)
{
	s_error = 0;
	data->env = ft_arrdup(data->env);
	data->dico = NULL;
	init_vars(data);
	init_dico(data);
}

void display_data(t_data *data)
{
	char **cmd;
	void *tmp;

	tmp = data->dico;
	printf("------------------DICO-------------------\n");
	while (data->dico)
	{
		cmd = data->dico->content;
		printf("%s=", cmd[0]);
		if (cmd[1])
			printf("%s\n", cmd[1]);
		data->dico = data->dico->next;
	}
	data->dico = tmp;
	printf("------------------END / DICO-------------------\n");
	printf("------------------OTHER info-------------------\n");
	printf("quit : %d\n", data->quit);
	printf("quotes_hd : %d\n", data->quotes_hd);
	printf("n_cmd : %d\n", data->n_cmd);
	printf("------------------END / OTHER info-------------\n");
}