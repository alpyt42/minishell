/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:43:12 by amontalb          #+#    #+#             */
/*   Updated: 2023/03/14 11:18:23 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern int	s_error;

static char **split_all(char **cmd, t_data *data)
{
    char    **cmdsplit;
    int     i;
    
    i = -1;
    (void) data;
    while (cmd[++i])
    {
        cmdsplit = ft_cmdsplit(cmd[i], "<|>");
        if (!cmdsplit)
            return (cmd);
        cmd = ft_replace_in_matrix(cmd, cmdsplit, i);
        // ft_free_matrix(cmdsplit);
    }
    return (cmd);
}




int	check_error(char *cmd)
{
	int	i;
	int	simple_q;
	int	double_q;
	
	i = 0;
	simple_q = 0;
	double_q = 0;
	while (cmd[i])		
	{
		simple_q = (simple_q + (!double_q && cmd[i] == '\'')) % 2 ;
        double_q = (double_q + (!simple_q && cmd[i] == '\"')) % 2 ;
		if (!simple_q && !double_q && (cmd[i] == ';' || cmd[i] == '\\' 
        || (cmd[i] == '|' && cmd[i + 1] && cmd[i + 1] == '|')
        || (cmd[i] == '&' && cmd[i + 1] && cmd[i + 1] == '&')))
			return (1);
        i++;
	}
	if (simple_q == 1 || double_q == 1)
		return (1);
	return (0);
}



int check_pars(char *cmd, t_data *data)
{
    char **parsed;

    parsed = NULL;
    if(check_error(cmd))
    {
        ft_dprintf(1, "error arg\n");
        return (1);
    }
    parsed = cmdlexing(cmd);
    free(cmd);
    parsed = split_all(parsed, data);
    data->cmds = fill_nodes(parsed, data);
    return (0);
}