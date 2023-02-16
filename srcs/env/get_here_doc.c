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

int	s_error = 0;

static char *get_var_hd(char *del, t_data *data)
{

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
		// dprintf(1,"ft_strlen(readstr) - 1:%ld ft_strlen(del):%ld ft_strncmp(del, readstr, ft_strlen(readstr) - 1):%d\n", ft_strlen(readstr), ft_strlen(del), ft_strncmp(del, readstr, ft_strlen(readstr) - 1) );
		// dprintf(1, "del : $%s$\nreadstr : $%s$\n", del, readstr);
		if (!readstr)
		{
			ft_dprintf(2, "%s : %s", warn, del);
			break ;
		}
		if (!ft_strncmp(del, readstr, ft_strlen(readstr))\
			&& ft_strlen(readstr) == ft_strlen(del))
			break ;
		line = ft_strjoin(line, readstr);
		tmp = line;
		line = ft_strjoin(line, "\n");
		free(tmp);
		free(readstr);
	}
	return (line);
}

int	get_here_doc(char *del, int quotes, t_data *data)
{
	int		fd[2];
	char	*warning;
	char	*str;
	char	*tmp;

	s_error = 0;
	warning = "minishell: warning: here-document delimited by end-of-file";
	// dprintf(1, "del : %s\n", del);
	if (!del || ft_strchr(del, '<') || ft_strchr(del, '|'))
		return(errors("minishell: syntax error near unexpected token", del, 1));
	if (pipe(fd) == -1)
		perror("pipe");
	str = fill_here_doc(del, warning);
	if (quotes == 1)
		tmp = get_var_hd(str, data);
	free(str);
	str = tmp;
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
