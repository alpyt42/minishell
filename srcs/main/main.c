/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/06 13:33:51 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	// t_shell shell;
	t_data  data;
    char    *prompt;
	char    *command;
    
    data.env = env;
    data.argv = argv;
	init_data(&data);
    // if (check_data(&data))
        // return (ft_dprintf(1, "env: ‘minishell’: No such file or directory\n"), 127);
    display_list(&data);
    while(argc && argv)
    {
        signal(SIGINT, signal_receive);
		signal(SIGQUIT, SIG_IGN);
        prompt = get_prompt(&data);
        command = readline(prompt);
        if (!command || (!ft_strncmp(command, "exit", 4) && ft_strlen(command) == 4))
        {
            ft_dprintf(1, "exit\n");
            exit(1);
        }
        add_history(command);
        ft_dprintf(1, "command : $%s$\n", command);
        free(prompt);
    }
    return (0);   
}
