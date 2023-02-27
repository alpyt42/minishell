/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:18:11 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/06 13:00:07 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		nb = nb * 10 + str[i++] - 48;
	}
	if (nb == 0 && str[0] != '0' && str[1] == '\0')
		return (0);
	return (sign * nb);
}

long	ft_atoi_long(char *str)
{
	size_t	i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	if (!str)
		return (2147483649);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (2147483649);
		nb = nb * 10 + str[i++] - 48;
	}
	if (nb == 0 && str[0] != '0' && str[1] == '\0')
		return (2147483649);
	return (sign * nb);
}