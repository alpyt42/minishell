/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 08:47:16 by amontalb          #+#    #+#             */
/*   Updated: 2023/03/08 13:17:41 by amontalb         ###   ########.fr       */
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
			while (cmd[i] && (!ft_strchr(s, cmd[i]) || double_q || simple_q))		
			{
				simple_q = (simple_q + (!double_q && cmd[i] == '\'')) % 2 ;
      			double_q = (double_q + (!simple_q && cmd[i] == '\"')) % 2 ;
				i++;
			}
			if ((simple_q == 1) || (double_q == 1))
				return (-1);
		} 
		else
			i++;		
	}
	return(words);
}

static char **fill_array(char **cmdlex, char *cmd, char *s)
{
	int	simple_q;
	int	double_q;
	int	i;
	int j;
	int k;

	i = 0;
	k = 0;
	simple_q = 0;
	double_q = 0;
	while (cmd[i])
	{
		while (cmd[i] && ft_strchr(s, cmd[i]))
			i++;
		j = i;
		while (cmd[i] && (!ft_strchr(s, cmd[i]) || double_q || simple_q))		
		{
			simple_q = (simple_q + (!double_q && cmd[i] == '\'')) % 2 ;
        	double_q = (double_q + (!simple_q && cmd[i] == '\"')) % 2 ;
			i++;
		}
		if (i > (int)ft_strlen(cmd))
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
	// char	**tmp;
	int		nbr_words;

	nbr_words = count_word(cmd, " ");
	if (nbr_words == -1)
		return (NULL);
	cmdlex = ft_calloc(sizeof(char *), (nbr_words + 1));
	// tmp = cmdlex;
	if (!cmdlex)
		return (NULL);
	cmdlex = fill_array(cmdlex, cmd, " ");
	// ft_free_arr(tmp);
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