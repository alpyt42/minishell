/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:39:52 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/12 01:53:07 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	get_exec_res(char ***res, int fd)
{
	char	**tab;
	char	*tmp;
	char	*line;

	tab = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strtrim(line, "\n");
		free(line);
		tab = ft_append_tab(tab, tmp);
		free(tmp);
	}
	ft_free_arr(*res);
	*res = tab;
}

void	exec_cmd_path(char ***res, char *path, char *cmd, char **env)
{
	pid_t	pid_fork;
	int		fd[2];
	char	**cmd_exec;

	if (pipe(fd) == -1)
			symbol_errors(strerror(errno), "", 0);
	pid_fork = fork();
	if (pid_fork == -1)
			symbol_errors(strerror(errno), "", 0);
	if (!pid_fork)
	{
		close(fd[0]);
		cmd_exec = ft_split(cmd, ' ');
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			symbol_errors(strerror(errno), "", 0);
		close(fd[1]);
		if (!access(path, F_OK))
			if (execve(path, cmd_exec, env) == -1)
				symbol_errors(strerror(errno), cmd_exec[0], 0);
		exit(1);
	}
	close(fd[1]);
	waitpid(pid_fork, NULL, 0);
	get_exec_res(res, fd[0]);
	close(fd[0]);
}