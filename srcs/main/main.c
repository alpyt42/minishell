/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/30 09:26:58 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <unistd.h>

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
    
	(void)argc;
	(void)argv;
	(void)env;

    init_data(&data, env);
	// char *command;

    // while(1) {
    //     command = readline("minishell> ");
    //     add_history(command);

    //     free(command);
    // }
    // printf("<<%s>>>\n", getcwd(NULL, 0));

    return 0;   
}