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
	t_node		*node;
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
	nb_ex = (nb_ex + 256) % 256;
	return (nb_ex);
}

int	built_pwd(void)
{
	char	*b_pwd;

	b_pwd = getcwd(NULL, 0);
	if (!b_pwd)
	{
		ft_dprintf(2, "minishell : %s", strerror(errno));
		return(errno);
	}
	ft_dprintf(2, "%s", b_pwd);
	free(b_pwd);
	return(0);
}

int	built_echo(t_data *data)
{
	char	**str;
	int		i;
	int		new_line;

	new_line = 1;
	i = 0;
	str = ((t_node *)data->cmds->content)->all_cmd;
	if (!str)
		return (0);
	while(str && str[++i])
	{
		if (str && str[0] && str[1] && !ft_strncmp(str[1], "-n", 2)
		&& ft_strlen(str[1]) == ft_strlen("-n") && i == 1)
			new_line = 0;
		else
		{
			ft_putstr_fd(str[i], 1);
			if (str[i + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	built_cd(t_data *data)
{
	char	**str;

	str = ((t_node *)data->cmds->content)->all_cmd;
	
}