/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:33:30 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/15 19:38:25 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
	data->cmds = NULL;
	data->dico = NULL;
	data->quit = 0;
	data->n_cmd = 0;
	data->env = ft_arrdup(data->env);
	init_vars(data);
	init_dico(data);
}

void display_data(t_data *data)
{
	t_node *cmd;
	void *tmp;

	tmp = data->cmds;
	while (data->cmds)
	{
		cmd = data->cmds->content;
		int i = 0;
		while(cmd->all_cmd[i])
		{
			printf("cmd[%d] %s\n", i, cmd->all_cmd[i]);
			i++;
			printf("_______\n");
		}
		data->cmds = data->cmds->next;
	}
	data->cmds = tmp;
}