/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/30 21:59:11 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void   init_data(t_data *data, char **envp)
{
    init_dico(data, envp);
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

int main(int argc, char **argv, char** env)
{
	// t_shell shell;
	t_data  data;
    char    *user;
    char    *cmd_pwd;
	char *command;

	(void)argc;
	(void)argv;
	(void)env;
    init_data(&data, env);
    search_dico("PWD", &data);
    while(1)
    {
        user = search_dico("USER", &data);
        cmd_pwd = search_dico("PWD", &data);
        ft_dprintf(1, "%s@minishell:~%s", user, cmd_pwd);
        command = readline("$>");
        if (!command || (!ft_strncmp(command, "exit", 4)\
            && ft_strlen(command) == 4))
            exit(1);
        add_history(command);
        ft_dprintf(1, "$%s$\n", command);
    }
    return 0;   
}