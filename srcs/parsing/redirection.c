/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:08:47 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/28 10:37:35 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

int get_fd(int oldfd, char *path, int create, int append)
{
    int fd;
    
    if (oldfd > 2)
		close(oldfd);
    if (!path)
        return (-1);
    // if(access(path, F_OK) == -1 && !create)
    //     error();
    // else if (access(path, R_OK) == -1 && !create)
    //     error();
    // else if (access(path, W_OK) == -1 && access(path, F_OK) == 0 && create)
    //     error();
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

t_node  *get_out1(t_node *node, char **cmds, int *i)
{
    (*i)++;
    if (cmds[*i])
    {
        node->outfile = get_fd(node->outfile, cmds[*i], 1, 0);
        (*i)++;
    }

    return (node);
}

t_node  *get_out2(t_node *node, char **cmds, int *i)
{
    (*i)++;
    if (cmds[*i])
    {
        node->outfile = get_fd(node->outfile, cmds[*i], 1, 1);
        (*i)++;
    }

    return (node);    
}

t_node  *get_in1(t_node *node, char **cmds, int *i)
{
    (*i)++;
    if (cmds[*i])
    {
        node->outfile = get_fd(node->outfile, cmds[*i], 0, 0);
        (*i)++;
    }

    return (node);    
}

// t_node  *get_in2(t_data *data, t_node *node, char **cmds, int *i)
// {
    
//     (*i)++;
//     if(cmds[*i])
//         node->infile = get_here_doc(cmds[*i], data);
    
//     return (node)
// }
