/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:33:30 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/28 14:51:15 by amontalb         ###   ########.fr       */
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

void init_struct(t_data *data)
{
	data->cmds = NULL;
	data->dico = NULL;
	data->env = NULL;
	data->argv = NULL;
	data->quit = 0;
	data->quotes_hd = 0;
	data->n_cmd = 0;
}

void init_data(t_data *data)
{
	s_error = 0;
	// init_struct(data);
	data->env = ft_arrdup(data->env);
	data->dico = NULL;
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
		printf("%s\n", cmd->all_cmd[i]);
		i++;
		printf("_______\n");
		}
		printf("<<<<>>>>>\n");
		data->cmds = data->cmds->next;
	}
	data->cmds = tmp;
}