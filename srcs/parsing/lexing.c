/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 08:47:16 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/16 16:41:02 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	count_word(char *cmd, char *s)
{
	int	words;
	int	simple_q;
	int	double_q;
	int	i;

	i = 0;
	words = 0;
	while (cmd[i])
	{
		if (!ft_strchr(s, cmd[i]))
		{
			simple_q = 0;
			double_q = 0;
			words++;
			while (cmd[i] && (!ft_strchr(s, cmd[i]) || double_q == 1 || simple_q == 1))		
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

char **fill_lexing2(char **cmdlex, char *cmd, char *s)
{
	int	simple_q;
	int	double_q;
	int	i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (cmd[i])
	{
		while (cmd[i] && ft_strchr(s, cmd[i]))
			i++;
		j = i;
		simple_q = 0;
		double_q = 0;
		while (cmd[i] && (!ft_strchr(s, cmd[i]) || double_q == 1 || simple_q == 1))		
		{
			if (cmd[i] == '\"' && simple_q == 0)
				double_q += 1;
			if (cmd[i] == '\'' && double_q == 0)
				simple_q += 1;
			i++;
			if (simple_q == 2 || double_q == 2)
				break;
		}
		if (i > (int)strlen(cmd))
			cmdlex[k++] = NULL;
		else if(simple_q == 2 || double_q == 2)
			cmdlex[k++] = ft_substr(cmd, j + 1, i - j - 2);	
		else
			cmdlex[k++] = ft_substr(cmd, j, i - j);		
	}
	return (cmdlex);
}


char	**cmdlexing(char *cmd)
{
	char	**cmdlex;
	int		nbr_words;
	nbr_words = count_word(cmd, " ");
	if (nbr_words == -1)
		return (NULL);
	cmdlex =(char **) malloc (sizeof(char *) * (nbr_words + 1));
	if (!cmdlex)
		return (NULL);
	cmdlex = fill_lexing2(cmdlex, cmd, " ");
	return (cmdlex);
}

// int	main()
// {
// 	int i = 0;
// 	// printf("%s\n", "\"ok \" tout \"  \" le monde ");
// 	// printf("count_word : %d", lenght_word("\"ok\'\" tout \" ' \" \" ' \"le monde ", ' '));
// 	char **finito = cmdlexing(" echo \"hello      there\" how are \'you \'doing? $USER |wc -l >outfile");
// 	while (finito[i])
// 	{
// 		printf("%s\n", finito[i]);
// 		i++;
// 	}

// 	return  0;
// }