/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/21 12:09:23 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	get_pid(t_data *data)
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

static int	special_mini(int argc, t_data *data)
{
	char	*prompt;

	if (!argc)
		return (0);
	data->exe = 1;
	signal(SIGINT, signal_receive);
	signal(SIGQUIT, SIG_IGN);
	prompt = get_prompt(data);
	if (argc >= 2 && data->argv && data->argv[1][0] == '-'
		&& data->argv[1][1] == 'c' && data->argv[2])
		launch_mini(data, data->argv[2]);
	else if (argc >= 2)
	{
		ft_dprintf(2, ": No such file or directory\n");
		return (127);
	}
	free(prompt);
	rl_clear_history();
	return (g_error);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*prompt;
	char	*cmd;

	data.env = env;
	data.argv = argv;
	init_data(&data);
	if (argc >= 2 || !argc)
		return (special_mini(argc, &data));
	ft_dprintf(1, "\033[1;90mMINI.SHELL  |  ale-cont \\ amontalb\033[0;39m\n");
	while (argc && argv)
	{
		data.exe = 1;
		signal(SIGINT, signal_receive);
		signal(SIGQUIT, SIG_IGN);
		prompt = get_prompt(&data);
		if (!prompt)
			prompt = ft_strdup("minishell $ ");
		dprintf(1, "%s", prompt);
		cmd = get_next_line(0);
		free(prompt);
		if (!launch_mini(&data, cmd) || data.quit)
			break ;
	}
	return (rl_clear_history(), g_error);
}
