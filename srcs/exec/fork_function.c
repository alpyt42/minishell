/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:58:56 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/08 14:46:04 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

static void	exec_cmd(t_data *d)
{
	t_node	*n;

	n = d->cmds->content;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(n) > 0)
		s_error = exec_builtin(d, n);
	else if (is_builtin(n) < 0 && n->all_cmd && n->all_path)
		execve(n->all_path, n->all_cmd, d->env);
}

static void	*redir_dup(t_list *cmds, int fd[2])
{
	t_node	*n;

	n = cmds->content;
	if (n->infile != STDIN_FILENO)
	{
		if (dup2(n->infile, STDIN_FILENO) == -1)
			return(print_error(DUPERR, NULL, NULL, 1));
		close(n->infile);
	}
	if (n->outfile != STDOUT_FILENO)
	{
		if (dup2(n->outfile, STDOUT_FILENO) == -1)
			return(print_error(DUPERR, NULL, NULL, 1));
		close(n->outfile);
	}
	else if (cmds->next && dup2(fd[1], STDOUT_FILENO) == -1)
		return (print_error(DUPERR, NULL, NULL, 1));
	close(fd[1]);
	return ("");
}

static void	*get_fork(t_data *d, int fd[2])
{
	pid_t	pdt;

	pdt = fork();
	if (pdt == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (print_error(FORKERR, NULL, NULL, 1));
	}
	else if (pdt == 0)
	{
		redir_dup(d->cmds, fd);
		close(fd[0]);
		exec_cmd(d);
		exit(s_error);
	}
	return (NULL);
}

void	*fork_fct(t_data *d, int fd[2])
{
	t_node	*n;
	DIR		*dir;

	dir = NULL;
	n = d->cmds->content;
	if (!n || !n->all_cmd || n->outfile < 0 || n->infile < 0)
		return (NULL);
	if (n->all_cmd)
		dir = opendir(*n->all_cmd);
	if (is_builtin(n) >= 0 || (n->all_path && !access(n->all_path, X_OK)))
		get_fork(d, fd);
	else if (is_builtin(n) < 0 && (dir ||
		(n->all_path && !access(n->all_path, F_OK))))
		s_error = 126;
	else if (is_builtin(n) < 0 && n->all_cmd)
		s_error = 127;
	if (dir)
		closedir(dir);
	return("");
}
