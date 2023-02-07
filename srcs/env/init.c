/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:33:30 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/07 14:38:07 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_data(t_data *data)
{
    (void)data;
    return (0);
}

static void init_shlvl(t_data *data)
{
    char	*shlvl;

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

static void	init_vars(t_data *data)
{
	char	*pwd;
    char    *underscore;
    char    *path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("no_path_found");
	set_env_vars(data, "PWD=", pwd);
	init_shlvl(data);
	free(pwd);
    path = find_in_arr(data->env, "PATH=");
    if (!path)
        set_env_vars(data, "PATH=",\
        "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
    underscore = find_in_arr(data->env, "_=");
    if (!underscore)
        set_env_vars(data, "_=", data->argv[0]);
}

void	init_data(t_data *data)
{
    data->env = ft_arrdup(data->env);
    data->dico = NULL;
    init_vars(data);
    init_dico(data);
    if (check_data(data))
    {
        ft_dprintf(2, "env: '%s': No such file or directory",\
            data->argv[0]);
        exit(check_data(data));
    }
    // char **test;
    // while (data->dico)
    // {
    //     test = data->dico->content;
    //     printf("%s\n", test[0]);
    //     // printf("%s\n", test[1]);
    //     data->dico = data->dico->next;
    // }
    // printf("<<%s>>>\n", search_dico("LESS", data));
}

void	display_list(t_data *data)
{
    char	**cmd;
    void	*tmp;
 
    tmp = data->dico;
    while(data->dico)
    {
        cmd = data->dico->content;
        printf("%s=", cmd[0]);
        if (cmd[1])
            printf("%s\n", cmd[1]);
        data->dico = data->dico->next;
    }
	data->dico = tmp;
}