/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/14 12:18:06 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

int main(int argc, char **argv, char **env)
{
	t_data data;
	char *prompt;
	char *command;
	// --------------------------------------------
	// char **tab = ft_calloc(sizeof(char), 4);
	// tab[0] = ft_strdup("SALUT");
	// tab[1] = ft_strdup("Les");
	// tab[2] = ft_strdup("gars");
	// char **insert = ft_calloc(sizeof(char), 2);
	// insert[0] = ft_strdup("petit");
	// ft_replace_in_matrix(&tab, insert, 1);
	// int i = 0;
	// ft_dprintf(1, "test");
	// while(tab[i])
	// 	printf("%s\n", tab[i++]);
	// exit(0);
	// ------------------for : here_doc
	// int fd = get_here_doc("EOF");
	// if (fd == -1)
	// 	exit (2);
	// char buf[20];
	// int i = 0;
	// while (read(fd, buf, 20) != 0)
	// 	printf("\nbuf n.%d : %s", i++, buf);
	// exit(0);
	// --------------------------------------------
	data.env = env;
	data.argv = argv;
	init_data(&data);
	ft_dprintf(1, "\033[1;90mMINI.SHELL  |  ale-cont \\ amontalb\033[0;39m\n");
	// display_list(&data);
	while (argc && argv)
	{
		signal(SIGINT, signal_receive);
		signal(SIGQUIT, SIG_IGN);
		prompt = get_prompt(&data);
		if (!prompt)
			command = readline("minishell $ ");
		else
			command = readline(prompt);
		if (!launch_mini(&data, command))
			break;
		ft_dprintf(1, "command : $%s$\n", command);
		free(prompt);
	}
	exit(s_error);
}
