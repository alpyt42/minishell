/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/27 10:45:51 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void   init_data(t_data *data, char **env)
{
    data->env = env; 
    int i = 0;
    while (data->env[i])
    {
        printf("%s\n", data->env[i++]);
    }   
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

    return 0;   
}