/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:39:44 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/30 19:38:11 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

void	print_error(int type, char *cmd, char *arg, int error)
{
	s_error = error;
	if (type == QUOTE)
		ft_dprintf(2, "minishell: error while looking for matching quote\n");
	else if (type == NDIR)
		ft_dprintf(2, "minishell: %s: %s: No such file or directory\n", cmd, arg);
	else if (type == NPERM)
		ft_dprintf(2, "minishell: %s: %s: permission denied\n", cmd, arg);
	else if (type == NCMD)
		ft_dprintf(2, "minishell: %s: %s: command not found\n", cmd, arg);
	else if (type == DUPERR)
		ft_dprintf(2, "minishell: dup2 failed\n");
	else if (type == FORKERR)
		ft_dprintf(2, "minishell: fork failed\n");
	else if (type == PIPERR)
		ft_dprintf(2, "minishell: error creating pipe\n");
	else if (type == PIPENDERR)
		ft_dprintf(2, "minishell: syntax error near unexpected token `|'\n");
	else if (type == MEM)
		ft_dprintf(2, "minishell: no memory left on device\n");
	else if (type == IS_DIR)
		ft_dprintf(2, "minishell: %s: %s: Is a directory\n", cmd, arg);
	else if (type == NOT_DIR)
		ft_dprintf(2, "minishell: %s: %s: Not a directory\n", cmd, arg);
}

// void	ft_free_content(void *content)
// {

// }

// void	ft_free_mini(t_data *data)
// {

// }

int	errors(char *strerr, char *error, int n)
{
	if (n == 1)
	{
		if (ft_strchr(error, '<'))
			ft_dprintf(2,"%s %s",strerr, "'<'");
		else if (ft_strchr(error, '|'))
			ft_dprintf(2,"%s %s",strerr, "'|'");
		else if (ft_strchr(error, '>'))
			ft_dprintf(2,"%s %s",strerr, "'>'");
		return (-1);
	}
	ft_dprintf(2,"%s :%s",strerr, error);
	return(-1);
}
