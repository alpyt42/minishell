/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_alric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/08 17:35:16 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

static void	init_struct(t_data *data)
{
	s_error = 0;
	data->cmds = NULL;
	data->dico = NULL;
	data->env = NULL;
	data->quit = 0;
	data->n_cmd = 0;
}

int main(int argc, char **argv, char **env)
{
	t_data data;
	char *prompt;
	char *command;

	init_struct(&data);
	data.env = env;
	init_data(&data);
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
		if (!launch_mini(&data, command) || data.quit)
			break;
		free(prompt);
	}
	exit(s_error);
}
