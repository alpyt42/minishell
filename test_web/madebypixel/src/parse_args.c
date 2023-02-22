/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 12:08:12 by aperez-b          #+#    #+#             */
/*   Updated: 2023/02/22 00:33:37 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_status;

static char	**split_all(char **args, t_prompt *prompt)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, prompt);
		// printf("b[%d]%s\n", i, args[i]);
		args[i] = expand_path(args[i], -1, quotes, \
			mini_getenv("HOME", prompt->envp, 4));
		// printf("b[%d]%s\n", i, args[i]);
		// printf("c[%d]%s\n", i, args[i]);
		subsplit = ft_cmdsubsplit(args[i], "<|>");
		ft_matrix_replace_in(&args, subsplit, i);
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	return (args);
}

void display(t_list *cmds)
{
	int	i,j;
	
	j = 0;
	while (cmds)
	{
		i = -1;
		while (((t_mini *)cmds->content)->full_cmd[++i])
			dprintf(1, "node n.%d cmds[%d] : %s\n", j, i, ((t_mini *)cmds->content)->full_cmd[i]);
		dprintf(1, "node n.%d full_path : %s\n", j, ((t_mini *)cmds->content)->full_path);
		dprintf(1, "node n.%d infile : %d\n", j, ((t_mini *)cmds->content)->infile);
		dprintf(1, "node n.%d outfile : %d\n", j, ((t_mini *)cmds->content)->outfile);
		j++;
		cmds = cmds->next;
	}
}

static void	*parse_args(char **args, t_prompt *p)
{
	int	is_exit;
	int	i;
	char	**sp;

	sp = split_all(args, p);
	is_exit = 0;
	int j =-1;
	while (sp[++j])
		dprintf(2, "sp[%d] : %s\n", j, sp[j]);
	p->cmds = fill_nodes(sp, -1);
	display(p->cmds);
	if (!p->cmds)
		return (p);
	i = ft_lstsize(p->cmds);
	g_status = builtin(p, p->cmds, &is_exit, 0);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!is_exit && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 255;
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}
	return (p);
}

void	*check_args(char *out, t_prompt *p)
{
	char	**a;
	t_mini	*n;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	a = ft_cmdtrim(out, " ");
	free(out);
	if (!a)
		mini_perror(QUOTE, NULL, 1);
	if (!a)
		return ("");
	// int i = -1;
	// while (a[++i])
	// 	printf("a[%d]%s\n", i, a[i]);
	p = parse_args(a, p);
	if (p && p->cmds)
		n = p->cmds->content;
	if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
		p->envp = mini_setenv("_", n->full_cmd[ft_matrixlen(n->full_cmd) - 1], \
			p->envp, 1);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
