/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:52:13 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/16 16:29:45 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_fill_array(char **aux, char *s, char *set, int i[3])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	int j = 0;
	while (s && s[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, s[i[0]]))
		{
			while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
			{
				q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		aux[j] = ft_substr(s, i[1], i[0] - i[1]);
		printf("cmdsubslip[%d] :%s\n", j, aux[j]);
		j++;
	}
	return (aux);
}





char **cmdsplit(char *cmd,char *s)
{
	char **cmdsplit;
	int  nbrwords;

	nbrwords = count_word(cmd, "><|");
	if (nbrwords = - 1)
		return (NULL);
	cmdsplit = malloc((nbrwords + 1) * sizeof(char *));
	if (!cmdsplit)
		return (NULL);

	
	cmdsplit[nbrwords] = NULL;
	return (cmdsplit);
	
}