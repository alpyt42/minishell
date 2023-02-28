/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:14:36 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/24 16:45:45 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*fill_struct_test(t_data *data)
{
	t_list	*cmds = NULL;

	t_node	*node1 = ft_calloc(sizeof(t_node), 1);
	t_node	*node2 = ft_calloc(sizeof(t_node), 1);

	node1->all_cmd = ft_calloc(sizeof(char *), 2);
	node1->all_path = ft_calloc(sizeof(char), 30);
	node1->all_path = NULL;

	node2->all_cmd = ft_calloc(sizeof(char *), 2);
	node2->all_path = ft_calloc(sizeof(char), 30);
	node2->all_path = NULL;

	node1->all_cmd[0] = "exit";
	node1->all_cmd[1] = "25";
	node1->infile = 0;
	node1->outfile = 1;

	node2->all_cmd[0] = "cat";
	node2->infile = 3;
	node2->outfile = 1;

	ft_lstadd_back(&cmds, ft_lstnew(node1));
	// ft_lstadd_back(&cmds, ft_lstnew(node2));
	data->n_cmd = 1;
	data->cmds = cmds;
	return (cmds);
}
