/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/02 16:07:36 by ale-cont         ###   ########.fr       */
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

static void display_list(t_data *data)
{
    char	**cmd;
    void	*tmp;
    int     i;

    
    i = 0;
    tmp = data->dico;
    while(data->dico)
    {
        printf("l.%d  -  ", i++);
        cmd = data->dico->content;
        printf("%s : ", cmd[0]);
        if (cmd[1])
            printf("%s\n", cmd[1]);
        data->dico = data->dico->next;
    }
	data->dico = tmp;
}

int main(int argc, char **argv, char** env)
{
	// t_shell shell;
	t_data  data;
    char    *prompt;
	char    *command;
    
    data.env = env;
	init_data(&data, env);
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
    return 0;   
}
