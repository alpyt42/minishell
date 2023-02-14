/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:00 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/14 19:22:34 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	s_error;

char	*fill_here_doc(char *del, char warn)
{
	char	*line;
	char	*readstr;
	char	*tmp;

	line = NULL;
	readstr = NULL;
	while (s_error != 130)
	{
		tmp = line;
		readstr = readline("> ");
		if (!readstr)
		{
			ft_dprintf(2, "%s", del);
			break ;
		}
		if (!ft_strncmp(readstr, del, ft_strlen(readstr) - 1)\
			&& ft_strlen(readstr) - 1 == ft_strlen(del))
			break ;
		line = ft_strjoin(line, readstr);
		free(line);
	}
	free(line);
	return (line);
}

int	get_here_doc(char *del)
{
	int		fd[2];
	char	*warning;
	char	*str;

	s_error = 0;
	warning = "minishell: warning: here-document delimited by end-of-file";
	if (ft_strchr(del, "<") || ft_strchr(del, "|"))
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token '%s'", del);
		return (NULL);
	}
	if (pipe(fd) == -1)
		perror("pipe");
	str = fill_here_doc(del, warning);
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
