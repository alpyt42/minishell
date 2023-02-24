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

void	display_arr(char **arr, char *info)
{
	if (!arr)
		return ;
	int i = -1;
	while (arr[++i])
	{
		printf("%s", info);
		printf("[%d] : %s\n", i, arr[i]);
	}
}

void	display_cmd(t_list *cmds)
{
	int	i,j;
	
	j = 0;
	while (cmds)
	{
		i = -1;
		while (((t_node *)cmds->content)->all_cmd[++i])
			dprintf(1, "node n.%d cmds[%d] : %s\n", j, i, ((t_node *)cmds->content)->all_cmd[i]);
		dprintf(1, "node n.%d full_path : %s\n", j, ((t_node *)cmds->content)->all_path);
		dprintf(1, "node n.%d infile : %d\n", j, ((t_node *)cmds->content)->infile);
		dprintf(1, "node n.%d outfile : %d\n", j, ((t_node *)cmds->content)->outfile);
		j++;
		cmds = cmds->next;
	}
}

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

	node1->all_cmd[0] = "ls";
	node1->all_cmd[1] = "-l";
	node1->infile = 0;
	node1->outfile = 1;

	node2->all_cmd[0] = "cat";
	node2->infile = 3;
	node2->outfile = 1;

	ft_lstadd_back(&cmds, ft_lstnew(node1));
	ft_lstadd_back(&cmds, ft_lstnew(node2));
	data->n_cmd = 2;
	return (cmds);
}
