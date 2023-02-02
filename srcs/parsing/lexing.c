/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 08:47:16 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/02 16:42:41 by amontalb         ###   ########.fr       */
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

	while (cmd[i])
	{
		if (cmd[i] != s)
		{
		simple_q = 0;
		double_q = 0;
			words++;
			while (cmd[i] && (cmd[i] != s || double_q == 1))		
			{
				if (cmd[i] == '\"' && simple_q == 0)
					double_q += 1;
				if (cmd[i] == '\'' && double_q == 0)
					simple_q += 1;
				i++;
				if (simple_q == 2 || double_q == 2)
					break;
			}
			if ((simple_q == 1) || (double_q == 1))
				return (-1);
		} 
		else
			i++;		
	}
	return(words);
}

char **fill_lexing(char **cmd, char s)
{
	int	simple_q;
	int	double_q;
	int	i;

	while (cmd[i])



	
}


char	**cmdlexing(char *cmd)
{
	char	**cmdlex;
	int		nbr_words;

	nbr_words = count_word(cmd, ' ');
	if (nbr_words == - 1)
		return (NULL);
	cmdlex =(char **) malloc (sizeof(char *) * (nbr_words + 1));
	if (!cmdlex)
		return (NULL);
	
	fil;
	cmdlex[nbr_words] = NULL;
	return (cmdlex);




	
}

int	main()
{
	printf("%s\n", "ok tout \"  \" le monde ");
	printf("count_word : %d", count_word(" ok tout \" ' \" \" ' \"le monde ", ' '));
	return  0;
}