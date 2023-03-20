/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:43:24 by amontalb          #+#    #+#             */
/*   Updated: 2023/03/20 17:49:24 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*init_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->all_cmd = NULL;
	node->all_path = NULL;
	node->infile = STDIN_FILENO;
	node->outfile = STDOUT_FILENO;
	return (node);
}

static char	**fill_nodes3(t_node *node, char *cmd, t_data *data)
{
	char	*temp;
	char	*temp2;
	char	**all_cmd;

	temp = expand_all2(cmd, data);
	temp2 = ft_strim_quotes(temp);
	all_cmd = ft_append_tab(node->all_cmd, temp2);
	if (temp)
		free(temp);
	if (temp2)
		free (temp2);
	return (all_cmd);
}

static t_node	*fill_nodes2(t_node *node, char **cmds, int *i, t_data *data)
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
			node->all_cmd = fill_nodes3(node, cmds[*i], data);
		else
		{
			symbol_errors("|", 2, &data->exe);
			*i = -2;
		}
	}
	return (node);
}

t_list	*fill_nodes(char **cmds, t_data *data)
{
	t_list	*begin;
	t_list	*temp;
	int		i;

	begin = NULL;
	i = -1;
	while (cmds && cmds[++i] && data->exe)
	{
		temp = ft_lstlast(begin);
		if ((cmds[i][0] == '|' && cmds[i + 1] && cmds[i + 1][0] == '|')
			|| (cmds[i][0] == '|' && !cmds[i + 1]))
			return (NULL);
		if (i == 0 || (cmds[i][0] == '|'
			&& cmds[i + 1] && cmds[i + 1][0] != '|'))
		{
			i += cmds[i][0] == '|';
			ft_lstadd_back(&begin, ft_lstnew(init_node()));
			temp = ft_lstlast(begin);
		}
		temp->content = fill_nodes2(temp->content, cmds, &i, data);
	}
	ft_free_arr(cmds);
	return (begin);
}
