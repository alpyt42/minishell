/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/26 10:03:38 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"





int	main(int argc, char **argv, char** env)
{
	// t_shell shell;
	
	(void)argc;
	(void)argv;
	(void)env;
	char *command;

    while(1) {
        command = readline("minishell> ");
        add_history(command);

        free(command);
    }

    return 0;   
}