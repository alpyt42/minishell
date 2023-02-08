/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:07:23 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/08 15:52:09 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

int	launch_mini(t_data *data, char *cmd)
{
	(void)data;
	if (!cmd || (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4))
	{
		ft_dprintf(1, "exit\n");
		return (0);
	}
	add_history(cmd);
	return (1);
}