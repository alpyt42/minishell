/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_alric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:53 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/24 17:04:55 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

int main(int argc, char **argv, char **env)
{
	t_data data;
	char *prompt;
	char *command;

	(void)argc;
	// (void)env;
	// (void)argv;
	(void)prompt;
	(void)command;
	(void)data;
	// -----------------------------------------
	data.env = env;
	data.argv = argv;
	init_data(&data);
	t_list *cmds = fill_struct_test(&data);
	ft_dprintf(1, "PRINT CMDS : \n");
	display_cmd(cmds);
	ft_dprintf(1, "PRINT T_DATA : \n");
	display_data(&data);
	ft_dprintf(1, "\033[1;90mMINI.SHELL  |  ale-cont \\ amontalb\033[0;39m\n");
	ft_dprintf(1, "------------------EXEC--------------\n");
	mini_process(&data);
	ft_dprintf(1, "----------------END_EXEC------------\n");
	return (0);
}