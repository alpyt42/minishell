/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:43:12 by amontalb          #+#    #+#             */
/*   Updated: 2023/03/01 09:00:51 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **split_all(char **cmd, t_data *data)
{
    char    **cmdsplit;
    int     i;
    
    i = -1;
    (void) data;
    // cmd = expand_all(cmd, data);
    while (cmd[++i])
    {
        cmdsplit = ft_cmdsplit(cmd[i], "<|>");
        cmd = ft_replace_in_matrix(cmd, cmdsplit, i);
        // ft_free_matrix(cmdsplit);
    }
    return (cmd);
}



// static void parse_args(char **cmd, t_data *data)
// {
//     data



// }




char *check_pars(char *cmd, t_data *data)
{
    char **parsed;
    (void) data;
    
    parsed = cmdlexing(cmd);
    // free(cmd);
    parsed = split_all(parsed, data);
    data->cmds = fill_nodes(parsed, data);

    
    // int i = -1;
    // while (parsed[++i])
    //     printf("--%s--\n", parsed[i]); 
    return (NULL);
}