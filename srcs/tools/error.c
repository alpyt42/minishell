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

// void	ft_free_content(void *content)
// {

// }

// void	ft_free_mini(t_data *data)
// {

// }

void	display_error(char *strerr, char *error)
{
	ft_dprintf(2,"%s %s",strerr, error);
	exit(EXIT_FAILURE);
}
