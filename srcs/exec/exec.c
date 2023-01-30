/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:39:52 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/30 19:37:55 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_exec_res(char **res, int fd)
{
	char	**tab;
	char	*line;

	tab = NULL;
	line = get_next_line(fd);
	while (line)
	{
		line = ft_strtrim(line, "\n");
		if (!tab)
			tab = ft_append_tab(NULL, line);
		tab = ft_append_tab(tab, line);
		free(line);
		line = get_next_line(fd);
	}
	ft_free_arr(res);
	res = tab;
}

void	exec_cmd_path(char **res, char *path, char *cmd, char **env)
{
	pid_t	pid_fork;
	int		fd[2];
	char	**cmd_exec;

	if (pipe(fd) == -1)
			display_error(strerror(errno), "");
	pid_fork = fork();
	if (pid_fork == -1)
			display_error(strerror(errno), "");
	if (!pid_fork)
	{
		close(fd[FD_READ]);
		if (dup2(fd[FD_WRITE], STDOUT_FILENO) == -1)
			display_error(strerror(errno), "");
		close(fd[FD_WRITE]);
		cmd_exec = ft_split(cmd, ' ');
		if (access(path, F_OK) == 0)
			if (execve(path, cmd_exec, env) == -1)
				display_error(strerror(errno), cmd_exec[0]);
		exit(1);
	}
	close(fd[FD_WRITE]);
	waitpid(pid_fork, NULL, 0);
	get_exec_res(res, fd[FD_READ]);
	close(fd[FD_READ]);
}