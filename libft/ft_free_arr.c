/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:32:22 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/04 17:17:50 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_arr(char **arr)
{
	int	i;
	i = 0;
	int j =-1;
	while (arr[++j])
		dprintf(2, "arr[%d] : %s, ptr : %p\n", j, arr[j], arr);
	if (!arr)
		return ;
	while (arr[i])
	{
		dprintf(2, "free : arr[%d] : %s, ptr : %p\n", i, arr[i], arr);
		free(arr[i++]);
	}
	// free(arr);
	// dprintf(1, "FIN");
}
