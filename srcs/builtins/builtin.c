/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:40:09 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/09 17:07:17 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

// int	check_builtin(t_data *data)
// {
	
// }

int	is_builtin(char *cmd)
{
	int			i;
	const char	*built[9];

	i = -1;
	built[0] = "pwd";
	built[1] = "cd";
	built[2] = "ls";
	built[3] = "echo";
	built[4] = "export";
	built[5] = "env";
	built[6] = "unset";
	built[7] = "exit";
	built[8] = NULL;
	while (built[++i])
		if (ft_strncmp(built[i], cmd, ft_strlen(cmd)) == 0
		&& ft_strlen(cmd) == ft_strlen(built[i]))
			return (1);
	return (0);
}
