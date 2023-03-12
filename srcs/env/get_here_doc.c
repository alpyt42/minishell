/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:00 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/12 21:00:54 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

extern int	s_error;

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
		del = ft_strjoin(str, &del[*i + 1 + ft_strchars_i(&del[*i + 1], "|/`!*@=><+-;#&$?~%^{}: \"\'\n\0")]);
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
			ft_dprintf(2, "%s : %s\n", warn, del);
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
	return (line);
}

int	get_here_doc(char *del, t_data *data)
{
	int		fd[2];
	char	*warning;
	char	*str;
	int		q;

	s_error = 0;
	q = 0;
	warning = "minishell: warning: here-document delimited by end-of-file";
	// dprintf(1, "delimiter : %s\n", del);
	if (!del || ft_strchr(del, '<') || ft_strchr(del, '|'))
		return(symbol_errors(del, 2, &data->exe));
	if (pipe(fd) == -1)
		print_error(PIPERR, NULL, NULL, errno);
	str = fill_here_doc(del, warning);
	if (q == 1 && str)
		str = get_var_hd(str, data);
	if (str)
		write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	free(str);
	if (s_error == 130)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
