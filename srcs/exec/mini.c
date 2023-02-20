/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:03:39 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/14 17:17:22 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

// int	mini_process(t_data *data)
// {
// 	char	*com;
// 	int		i;

// 	i = -1;
// 	data->p_ids = malloc(sizeof(int) * data->n_cmd);
// 	if (pipe(data->pipa) < 0 || pipe(data->pipb))
// 		return(errors(strerror(errno), "", 0));
// 	while (++i < data->n_cmd)
// 	{
// 		data->p_ids[i] = fork();
		
// 	}
//     return (0);
// }

int	launch_mini(t_data *data, char *cmd)
{
	(void)data;
	char	*cmd_trim;

	(void)cmd_trim;
	if (!cmd)
	{
		ft_dprintf(1, "exit\n");
		return (0);
	}
	if (cmd[0] != '\0')
		add_history(cmd);
	// s_error = mini_process(data);
	return (1);
}
