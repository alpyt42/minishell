/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:52:13 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/21 13:25:55 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_word(char *cmd, char *s)
{
	int	words;
	int	simple_q;
	int	double_q;
	int	i;

	i = 0;
	words = 0;
	while (cmd[i])
	{
		words++;
		if (!ft_strchr(s, cmd[i]))
		{
			simple_q = 0;
			double_q = 0;
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
	while (cmd[i])
	{
		j = i;
		if (!ft_strchr(s, cmd[i]))
		{
			while (cmd[i] && (!ft_strchr(s, cmd[i]) || double_q|| simple_q))		
			{
				simple_q = (simple_q + (!double_q && cmd[i] == '\'')) % 2 ;
        		double_q = (double_q + (!simple_q && cmd[i] == '\"')) % 2 ;
				i++;
			}
		}
		else
			i++;
		cmdlex[k] = ft_substr(cmd, j, i - j);
		k++;
	}
	return (cmdlex);
}



char **ft_cmdsplit(char *cmd, char *s)
{
	char **cmdsplit;
	int  nbrwords;
	
	// dprintf(2, "nbr_words\n");
	nbrwords = count_word(cmd, s);
	if (nbrwords == -1)
		return (NULL);
	cmdsplit = malloc((nbrwords + 1) * sizeof(char *));
	if (!cmdsplit)
		return (NULL);
	cmdsplit = fill_array(cmdsplit, cmd, s);
	cmdsplit[nbrwords] = NULL;
	return (cmdsplit);
}