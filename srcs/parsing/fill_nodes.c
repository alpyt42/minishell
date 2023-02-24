/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:43:24 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/24 16:28:22 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_node  *init_node(char **)
{
    t_node *node;

    node = malloc(sizeof(t_node));
    if (!node)
        return (NULL);
    node->all_cmd = NULL;
    node->all_path = NULL;
    node->infile = STDIN_FILENO;
    node->outfile = STDOUT_FILENO;
    return (node);
}


t_list *fill_nodes(char **cmds, int i)
{
    t_list  *cmds;
    t_list  *temp; 
    int     i;

    cmds[0] = NULL;
    i = -1;
    while(cmds[++i])
    {
        if (i == 0 || (cmds[i][0] == '|' && cmds[i + 1]))
        {
            i+= cmds[i][0] == '|';
            ft_lstadd_back(&cmds[0], init_node());
            temp = ft_lstlast(cmds[0]);
        }
        temp->content = get_params(temp)

    }


    
}