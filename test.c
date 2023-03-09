/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:24 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/09 13:55:20 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(void)
{
	int	fd1[2];
	int	fd2[2];
	int	fd3[2];
	int	fd4[2];
	int	fd5[2];
	int	fd6[2];
	int	fd7[2];
	
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	pipe(fd4);
	pipe(fd5);
	pipe(fd6);
	pipe(fd7);
	
	printf("fd1[0] : %d\n", fd1[0]);
	printf("fd1[1] : %d\n", fd1[1]);
	printf("fd2[0] : %d\n", fd2[0]);
	printf("fd2[1] : %d\n", fd2[1]);
	printf("fd3[0] : %d\n", fd3[0]);
	printf("fd3[1] : %d\n", fd3[1]);
	printf("fd4[0] : %d\n", fd4[0]);
	printf("fd4[1] : %d\n", fd4[1]);
	printf("fd5[0] : %d\n", fd5[0]);
	printf("fd5[1] : %d\n", fd5[1]);
	printf("fd6[0] : %d\n", fd6[0]);
	printf("fd6[1] : %d\n", fd6[1]);
	printf("fd7[0] : %d\n", fd7[0]);
	printf("fd7[1] : %d\n", fd7[1]);
}
