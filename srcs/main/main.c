/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/31 14:25:46 by ale-cont         ###   ########.fr       */
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
    char    *prompt;
	char    *command;

	(void)argc;
	(void)argv;
	(void)env;
    init_data(&data, env);
    search_dico("PWD", &data);
    while(1)
    {
        prompt = get_prompt(&data);
        // ft_dprintf(1,"prompt main : %s\n", prompt);
        command = readline(prompt);
        if (!command || (!ft_strncmp(command, "exit", 4) && ft_strlen(command) == 4))
            exit(1);
        add_history(command);
        ft_dprintf(1, "command : $%s$\n", command);
        free(prompt);
    }
    return 0;   
}
