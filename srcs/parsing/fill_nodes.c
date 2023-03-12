/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:43:24 by amontalb          #+#    #+#             */
/*   Updated: 2023/03/12 23:18:57 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
        if (cmds[*i][0] == '>' && cmds[*i + 1] && cmds[*i + 1][0] == '>')
            node = get_out2(node, cmds, i, data);
        else if (cmds[*i][0] == '>')
            node = get_out1(node, cmds, i, data);
        else if (cmds[*i][0] == '<' && cmds[*i + 1] && cmds[*i + 1][0] == '<')
            node = get_in2(data, node, cmds, i);
        else if (cmds[*i][0] == '<')
            node = get_in1(node, cmds, i, data);
        else if (cmds[*i][0] != '|')
            node->all_cmd = ft_append_tab(node->all_cmd, ft_strim_quotes(expand_all2(cmds[*i], data)));
        else
        {
            symbol_errors("|", 2, &data->exe);
            *i = -2;
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
        if ((cmds[i][0] == '|' && cmds[i + 1] && cmds[i + 1][0] == '|')
            || (cmds[i][0] == '|' && !cmds[i + 1]))
            return (NULL);
        if (i == 0 || (cmds[i][0] == '|' && cmds[i + 1] && cmds[i + 1][0] != '|'))
        {
            i+= cmds[i][0] == '|';
            ft_lstadd_back(&begin, ft_lstnew(init_node()));
            temp = ft_lstlast(begin);
        }
        temp->content = fill_nodes2(temp->content, cmds, &i, data);
    }
    ft_free_arr(cmds);
    return (begin);
}