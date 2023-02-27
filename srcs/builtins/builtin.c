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

int	is_builtin(char *cmd)
{
	int			i;
	const char	*built[9];

	i = -1;
	built[0] = "cd";
	built[1] = "export";
	built[2] = "exit";
	built[3] = "unset";
	built[4] = "ls";
	built[5] = "echo";
	built[6] = "env";
	built[7] = "pwd";
	built[8] = NULL;
	if (!cmd)
		return (-1);
	while (built[++i])
		if (ft_strncmp(built[i], cmd, ft_strlen(cmd)) == 0
		&& ft_strlen(cmd) == ft_strlen(built[i]))
			return (i);
	return (-1);
}

int	built_exit(t_data *data)
{
	t_node *node;
	long		nb_ex;

	nb_ex = 0;
	node = data->cmds->content;
	data->quit = 1;
	ft_putstr_fd("exit\n", 2);
	if (!data->cmds->next && !node->all_cmd[1])
		return (0);
	nb_ex = ft_atoi_long(node->all_cmd[1]);
	if (nb_ex == 2147483649)
	{
		ft_dprintf(2, "minishell: exit: %s", node->all_cmd[1]);
		ft_dprintf(2, ": numeric argument required\n");
		return(2);
	}
	else if (node->all_cmd[2])
	{
		data->quit = 0;
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	nb_ex %= 256 + 256 * (nb_ex < 0);
	printf("nb_ex : %ld\n", nb_ex);
	return (nb_ex);
}
