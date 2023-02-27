/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:08:47 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/27 17:13:19 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node  *getout1(t_node *node, char **cmds, int *i)
{
  (*i)++;
  if (cmds[*i])
    node->outfile = get_fd(node->outfile, cmds[*i], 1, 0);

    return (node);
}

t_node  *getout2(t_node *node, char **cmds, int *i)
{
    (*i)++;
    if (cmds[*i])
    node->outfile = get_fd(node->outfile, cmds[*i], 1, 1);

    return (node);    
}

t_node  *getin1(t_node *node, char **cmds, int *i)
{
    (*i)++;
    if (cmds[*i])
    node->outfile = get_fd(node->outfile, cmds[*i], 0, 0);

    return (node);    
}

t_node  *getin2(t_data *data, t_node *node, char **cmds, int *i)
{
    
    (*i)++;
    if(cmds[*i])
        node->infile = get_here_doc(cmds[*i], data);
    
    return (node)
}

int get_fd(int oldfd, char *path, int create, int append)
{
    int fd;
    
    if (oldfd > 2)
		close(oldfd);
    if (!path)
        return (-1);
    if(access(path, F_OK) == -1 && !create)
        error();
    else if (access(path, R_OK) == -1 && !create)
        error();
    else if (access(path, W_OK) == -1 && access(path, F_OK) == 0 && create)
        error();
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