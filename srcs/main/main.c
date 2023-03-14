/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/14 11:39:53 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

static void	get_pid(t_data *data)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
	{
		print_error(FORKERR, NULL, NULL, 1);
		exit(1);
	}
	if (!pid)
		exit(1);
	waitpid(pid, NULL, 0);
	data->p_ids = pid - 1;
}

int main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*prompt;
	char	*command;

	data.env = env;
	data.argv = argv;
	get_pid(&data);
	init_data(&data);
	// ft_dprintf(1, "\033[1;90mMINI.SHELL  |  ale-cont \\ amontalb\033[0;39m\n");
	while (argc && argv)
	{
		data.exe = 1;
		signal(SIGINT, signal_receive);
		signal(SIGQUIT, SIG_IGN);
		prompt = get_prompt(&data);
		if (argc >= 2 && argv && argv[1][0] == '-' && argv[1][1] == 'c' && argv[2])
		{
			launch_mini(&data, argv[2]);
			return (s_error);
		}
		else if (argc >= 2)
		{
			ft_dprintf(2, ": No such file or directory\n");
			return(127);
		}
		if (!prompt)
			command = readline("minishell $ ");
		else
			command = readline(prompt);
		free(prompt);
		if (!launch_mini(&data, command) || data.quit)
			break;
		// printf("s_error : %d\n", s_error);
	}
	rl_clear_history();
	exit(s_error);
}