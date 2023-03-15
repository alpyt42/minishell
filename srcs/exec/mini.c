/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:03:39 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/14 18:06:50 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int	s_error;

int	exec_builtin(t_data *d, t_node *n)
{
	if (is_builtin(n) == -1)
		return (0);
	if (is_builtin(n) == 0)
		s_error = built_cd(d, n);
	else if (is_builtin(n) == 1)
		s_error = built_export(d, n);
	else if (is_builtin(n) == 2)
		s_error = built_exit(d, n);
	else if (is_builtin(n) == 3)
		s_error = built_unset(d, n);
	else if (is_builtin(n) == 4)
		s_error = built_echo(n);
	else if (is_builtin(n) == 5)
		s_error = built_env(d, 0);
	else if (is_builtin(n) == 6)
		s_error = built_pwd();
	return (s_error);
}

// static void	*mini_no_pipe(t_data *d, t_node *n)
// {
// 	int	stdout_fd;
// 	int	stdin_fd;

// 	if (!n || n->infile < 0 || n->outfile < 0)
// 		return(0);
// 	stdout_fd = dup(STDOUT_FILENO);
// 	stdin_fd = dup(STDIN_FILENO);
// 	if (stdout_fd == -1)
// 		return(print_error(DUPERR, NULL, NULL, errno));
// 	if (n->infile != STDIN_FILENO)
// 	{
// 		if (dup2(n->infile, STDIN_FILENO) == -1)
// 			return(print_error(DUPERR, NULL, NULL, errno));
// 		close(n->infile);
// 	}
// 	if (n->outfile != STDOUT_FILENO)
// 	{
// 		if (dup2(n->outfile, STDOUT_FILENO) == -1)
// 			return(print_error(DUPERR, NULL, NULL, errno));
// 		close(n->outfile);
// 	}
// 	exec_builtin(d, n);
// 	if (n->infile > 2)
// 	{
// 		dup2(stdin_fd, STDOUT_FILENO);
// 		close(stdin_fd);
// 		close(n->infile);
// 	}
// 	if (n->outfile > 2)
// 	{
// 		dup2(stdout_fd, STDOUT_FILENO);
// 		close(stdout_fd);
// 		close(n->outfile);
// 	}
// 	return (NULL);
// }

void	*mini_process(t_data *data, t_list *cmds)
{
	t_node	*n;

	n = data->cmds->content;
	// if (data->n_cmd == 1 && is_builtin(n) >= 0)
	// 	return(mini_no_pipe(data, n));
	while(cmds)
	{
		if (!n->all_cmd)
			return (NULL);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec(data, cmds);
		}
		cmds = cmds->next;
	}
	return (NULL);
}

static void	get_error(t_data *d)
{
	// printf("s_error :%d \n", s_error);
	if (!d->quit && s_error == 13)
		s_error = 0;
	else if (s_error > 255)
		s_error = s_error / 255;
}

int	launch_mini(t_data *data, char *cmd)
{
	if (!cmd)
	{
		ft_dprintf(1, "exit\n");
		ft_free_mini(data);
		return (0);
	}
	if (ft_strlen(cmd) <= 0)
		return (1);
	if (cmd[0] != '\0')
		add_history(cmd);
	if (check_pars(cmd, data))
		return (1);
	data->n_cmd = ft_lstsize(data->cmds);
	if (data->n_cmd > 0 && data->exe)
		mini_process(data, data->cmds);
	if (data->n_cmd >= 1 || !(data->n_cmd == 1 && is_builtin(data->cmds->content)))
		while (data->n_cmd-- > 0)
			waitpid(-1, &s_error, 0);
	get_error(data);
	ft_lstclear(&data->dico, ft_free_dico);
	ft_lstclear(&data->cmds, ft_free_node);
	init_dico(data);
	return (1);
}
