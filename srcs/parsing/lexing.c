/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 08:47:16 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/01 10:45:15 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	count_word(char *cmd, char s)
{
	int	words;
	int	simple_q;
	int	double_q;
	int	i;

	i = 0;
	words = 0;
	simple_q = 0;
	double_q = 0;

	while (cmd[i])
	{
		if (cmd[i] != s)
		{
			words++;
			while ((cmd[i] != s && simple_q == 0 && double_q == 0)  && cmd[i] && simple_q != 2 && double_q != 2)
			{
				printf("%c\n", cmd[i]);
				if (cmd[i] == '\"' && simple_q == 0)
				{
					double_q += 1;
				}
				if (cmd[i] == '\'' && double_q == 0)
				{
					simple_q += 1;
				}
				i++;
			}
			printf("%d\n", double_q);
			if ((simple_q != 0 && simple_q != 2) || (double_q != 0 && double_q != 2))
				return (-1);
		} 
		else
			i++;		
	}
	return(words);
}

// char	**cmdlexing(char *cmd)
// {
// 	char	**cmdlex;
	




	
// }

int	main()
{
	printf("%d", count_word("ok tout\"  \" le monde ", ' '));
	return  0;
}