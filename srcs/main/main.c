/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/10 10:12:48 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	t_data  data;
    char    *prompt;
	char    *command;
    
    data.env = env;
    data.argv = argv;
	init_data(&data);

    // expand_vars("\'\"$USER\"\'", &data);
    expand_vars("$?", &data);
    return 0;
    // display_list(&data);
    while(argc && argv)
    {
        signal(SIGINT, signal_receive);
		signal(SIGQUIT, SIG_IGN);
        prompt = get_prompt(&data);
        command = readline(prompt);
        if (!command || (!ft_strncmp(command, "exit", 4) && ft_strlen(command) == 4))
        {
            ft_dprintf(1, "exit\n");
            exit(0);
        }
        add_history(command);
        ft_dprintf(1, "command : $%s$\n", command);
        free(prompt);
    }
    return (0);   
}
