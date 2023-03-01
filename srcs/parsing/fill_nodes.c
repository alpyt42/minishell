/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:43:24 by amontalb          #+#    #+#             */
/*   Updated: 2023/03/01 09:00:02 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

t_node  *init_node()
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

static t_node *fill_nodes2(t_node *node, char **cmds, int *i, t_data *data)
{
    if (cmds[*i])
    {
        if (cmds[*i][0] == '>' && cmds [*i + 1][0] == '>')
            node = get_out2(node, cmds, i);
        else if (cmds[*i][0] == '>')
            node = get_out1(node, cmds, i);
        // else if (cmds[*i][0] == '<' && cmds [*i + 1][0] == '<')
        //     node = get_in2(node, cmds, i);
        else if (cmds[*i][0] == '<')
            node = get_in1(node, cmds, i);
        if (cmds[*i] && cmds[*i][0] != '|')
        {
            node->all_cmd = ft_append_tab(node->all_cmd, expand_all2(cmds[*i], data));
        }
    }
    return (node);


}


t_list  *fill_nodes(char **cmds, t_data *data)
{
    t_list  *begin;
    t_list  *temp; 
    int     i;

    begin = NULL;
    i = -1;
    while(cmds[i] && cmds[++i])
    {
        temp = ft_lstlast(begin); 
        if (i == 0 || (cmds[i][0] == '|' && cmds[i + 1]))
        {
            i+= cmds[i][0] == '|';
            ft_lstadd_back(&begin, ft_lstnew(init_node()));
            temp = ft_lstlast(begin);
        }
        temp->content = fill_nodes2(temp->content, cmds, &i, data);
    }
    return (begin);
}