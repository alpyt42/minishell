/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:08:47 by amontalb          #+#    #+#             */
/*   Updated: 2023/03/12 23:23:11 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern int s_error;

int get_fd(int oldfd, char *path, int create, int append)
{
	int fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !create)
		print_error(NDIR, "ERROR", path, 1);
	else if (access(path, R_OK) == -1 && !create)
		print_error(NPERM, "ERROR", path, 126);
	else if (access(path, W_OK) == -1 && access(path, F_OK) == 0)
		print_error(NPERM, "ERROR", path, 126);
	if (create && append)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (create && !append)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!create && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_node *get_out1(t_node *node, char **cmds, int *i, t_data *data)
{
	(*i)++;
	if (cmds[*i])
		node->outfile = get_fd(node->outfile, cmds[*i], 1, 0);
	if (!cmds[*i] || node->infile == -1)
	{
		*i -= 1;
		if (node->infile != -1)
			symbol_errors("", 2, &data->exe);
		else
			s_error = 1;
	}
	return (node);
}

t_node *get_out2(t_node *node, char **cmds, int *i, t_data *data)
{
	(*i)++;
	(*i)++;
	if (cmds[*i])
		node->outfile = get_fd(node->outfile, cmds[*i], 1, 1);
	if (!cmds[*i] || node->infile == -1)
	{
		*i -= 1;
		if (node->infile != -1)
			symbol_errors("", 2, &data->exe);
		else
			s_error = 1;
	}
	return (node);
}

t_node *get_in1(t_node *node, char **cmds, int *i, t_data *data)
{
	(*i)++;
	if (cmds[*i])
		node->infile = get_fd(node->infile, cmds[*i], 0, 0);
	else
	{
		node->infile = -1;
		symbol_errors("", 2, &data->exe);
	}
	return (node);
}

t_node *get_in2(t_data *data, t_node *node, char **cmds, int *i)
{

	(*i)++;
	if (cmds[++(*i)])
		node->infile = get_here_doc(cmds[*i], data);
	if (!cmds[*i] || node->infile == -1)
	{
		*i -= 1;
		if (node->infile != -1)
			symbol_errors("", 2, &data->exe);
	}
	return (node);
}
