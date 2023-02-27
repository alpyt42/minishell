/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/27 15:04:23 by amontalb         ###   ########.fr       */
=======
/*   Updated: 2023/02/24 16:58:58 by ale-cont         ###   ########.fr       */
>>>>>>> f56778d4454d8e92ee4692fee22d863a03a9a7df
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

int main(int argc, char **argv, char **env)
{
	t_data data;
	char *prompt;
	char *command;

	// -----------------------------(void)---------
	(void)argc;
	(void)env;
	(void)argv;
	(void)prompt;
	(void)command;
	(void)data;
	// ------------------------------matrix_test---------
	// char **tab = ft_calloc(sizeof(char *), 4);
	// tab[0] = ft_strdup("SALUT");
	// tab[1] = ft_strdup("Les");
	// tab[2] = ft_strdup("gars");
	// tab[3] = NULL;
	// char **insert = ft_calloc(sizeof(char), 3);
	// insert[0] = ft_strdup("petit");
	// insert[1] = ft_strdup("kiki");
	// insert[2] = NULL;
	// char **newmat;
	// ft_replace_in_matrix(&newmat, tab, insert, 1);
	// int j =-1;
	// while (newmat[++j])
	// 	dprintf(2, "newmat[%d] : %s, ptr : %p\n", j, newmat[j], newmat[j]);
	// return (0);
	// int j =-1;
	// while (data.env[++j])
	// 	dprintf(2, "data.env[%d] : %s, ptr : %p\n", j, data.env[j], data.env[j]);
	// --------------------------------------------
	data.env = env;
	data.argv = argv;
	init_data(&data);
	// printf("%s\n", ft_strim_quotes("\'toto\'"));
	// --------------------for : parsing
	check_pars("echo toto lolo | wc | cat -l -t", &data);
	// check_pars(" echo \"hello      there\" | how << are \'you \'doing? ~ $USER$USER |wc -l >outfile ~", &data);
	display_list(&data);
	// ------------------for : here_doc
	// int fd = get_here_doc("ls", 1, &data);
	// if (fd == -1)
	// 	exit (2);
	// char buf[20] = {'\0'};
	// int i = 0;
	// while (read(fd, buf, 50) != 0)
	// 	printf("\nfd : %d / buf n.%d : %s", fd, i++, buf);
	// printf("FIN");
	return(0);
	// --------------------------------------------
	ft_dprintf(1, "\033[1;90mMINI.SHELL  |  ale-cont \\ amontalb\033[0;39m\n");
	
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
