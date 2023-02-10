/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:12:05 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/08 12:27:23 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	s_error;

// void	signal_receive(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		s_error = 130;
// 		ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 	}
// }
