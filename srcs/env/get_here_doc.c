/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:00 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/21 14:30:32 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	s_error = 0;

static char *sub_vars(char *del, t_data *data, int *i)
{
	char	*str;
	char	*var;
	char	*before;
	char	*user;
	int		searchd;

	before = ft_substr(del, 0, *i);
	searchd = ft_strchars_i(&del[*i + 1], "/`!*@=><+-;#&$?~%^{}: \"\'\n");
	user = ft_substr(del, *i + 1, searchd);
	var = search_dico(user, data);
	free(user);
	if (var)
		str = ft_strjoin(before, var);
	else
		str = ft_strdup(before);
	if (ft_strchars_i(&del[*i + 1], "|/`!*@=><+-;#&$?~%^{}: \"\'\n") != - 1)
		del = ft_strjoin(str, &del[*i + 1 + ft_strchars_i(&del[*i + 1], "|/`!*@=><+-;#&$?~%^{}: \"\'\0\n")]);
	else
		del = ft_strdup(str);
	if (var)
		(*i)++;
	free (before);
	free (str);
	return (del);
}

static char *get_var_hd(char *del, t_data *data)
{
	int		i;
	char	*tmp;
	
	i = 0;
	tmp = NULL;
	while (del && del[i])
	{
		if (del[i] == '$' && del[i + 1])
		{
			tmp = del;
			del = sub_vars(del, data, &i);
			free(tmp);
		}
		else
			i++;
	}
	return (del);
}

static char	*fill_here_doc(char *del, char *warn)
{
	char	*line;
	char	*readstr;
	char	*tmp;

	line = NULL;
	readstr = NULL;
	while (s_error != 130)
	{
		readstr = readline("> ");
		if (!readstr)
		{
			ft_dprintf(2, "%s : %s", warn, del);
			break ;
		}
		if (!ft_strncmp(del, readstr, ft_strlen(readstr))
			&& ft_strlen(readstr) == ft_strlen(del))
			break ;
		tmp = line;
		line = ft_strjoin(line, readstr);
		free(tmp);
		tmp = line;
		line = ft_strjoin(line, "\n");
		free(tmp);
		free(readstr);
	}
	dprintf(1, "line : %s", line);
	return (line);
}

int	get_here_doc(char *del, int quotes, t_data *data)
{
	int		fd[2];
	char	*warning;
	char	*str;

	s_error = 0;
	warning = "minishell: warning: here-document delimited by end-of-file";
	dprintf(1, "delimiter : --%s--\n", del);
	if (!del || ft_strchr(del, '<') || ft_strchr(del, '|'))
		return(errors("minishell: syntax error near unexpected token", del, 1));
	if (pipe(fd) == -1)
		perror("pipe");
	str = fill_here_doc(del, warning);
	if (quotes == 1)
		str = get_var_hd(str, data);
	dprintf(2, "str : %s", str);
	ft_dprintf(fd[1], "%s", str);
	free(str);
	close(fd[1]);
	if (s_error == 130)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
