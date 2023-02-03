/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 08:47:16 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/03 11:12:46 by amontalb         ###   ########.fr       */
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

int	lenght_word(char *cmd, char s)
{
	int	simple_q;
	int	double_q;
	int	i;
	int k;

	i = 0;
	k = 0;
	while (cmd[i] && k == 0)
	{
		if (cmd[i] != s)
		{
		simple_q = 0;
		double_q = 0;
			while (cmd[i] && (cmd[i] != s || double_q == 1))		
			{
				k = 1;
				if (cmd[i] == '\"' && simple_q == 0)
					double_q += 1;
				if (cmd[i] == '\'' && double_q == 0)
					simple_q += 1;
				i++;
				if (simple_q == 2 || double_q == 2)
					break;
			}
		}
		else
			i++;		
	}
	if (simple_q == 2 || double_q == 2)
		i -= 2;
	return (i);
}

char **fill_lexing(char **cmdlex, char *cmd, char s)
{
	int	simple_q;
	int	double_q;
	int	i;
	int k;

	k = 0;

	while (cmd[i])
	{
		cmdlex[k] = (char *)malloc(sizeof(char) * (lenght_word(cmd[i], ' ') + 1));
			int	simple_q;
			int	double_q;
		

	}


	
}


// char	**cmdlexing(char *cmd)
// {
// 	char	**cmdlex;
// 	int		nbr_words;

// 	nbr_words = count_word(cmd, ' ');
// 	if (nbr_words == - 1)
// 		return (NULL);
// 	cmdlex =(char **) malloc (sizeof(char *) * (nbr_words + 1));
// 	if (!cmdlex)
// 		return (NULL);
	
	
// 	cmdlex[nbr_words] = NULL;
// 	return (cmdlex);




	
// }

int	main()
{
	printf("%s\n", "\"ok \" tout \"  \" le monde ");
	printf("count_word : %d", lenght_word("\"ok\'\" tout \" ' \" \" ' \"le monde ", ' '));
	return  0;
}