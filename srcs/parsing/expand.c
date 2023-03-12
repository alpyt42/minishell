/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:11:15 by amontalb          #+#    #+#             */
/*   Updated: 2023/03/12 01:29:47 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern int	s_error;


char   *sub_path(char *cmd, t_data *data, int i)
{
    char    *before;
    char    *path;

    before = NULL;
    if(i != 0)
    {
        before = ft_substr(cmd, 0, i);
        path = ft_strjoin(before, search_dico("HOME", data));
        free (before);
    }
    else   
        path = ft_strdup(search_dico("HOME", data));
    i ++;
    if(cmd[i])
        path = ft_strjoin(path, &cmd[i]);
    free(cmd);
    return (path); 
}

char    *expand_path(char *cmd, t_data *data)
{
    int i;
    int simple_q;
	int double_q;
    int size_home;

    i = 0;
    simple_q = 0;
    double_q = 0;
    size_home = ft_strlen(search_dico("HOME", data));
    while (cmd[i])
    {
        simple_q = (simple_q + (!double_q && cmd[i] == '\'')) % 2 ;
        double_q = (double_q + (!simple_q && cmd[i] == '\"')) % 2 ;
        if (!simple_q && !double_q && cmd[i] == '~' && (i == 0 || cmd[i - 1] != '$'))
            {
                cmd = sub_path(cmd, data, i);
                i += size_home;
            }
        else
            i++;
    }
    return (cmd);
}

char    *sub_var(char *cmd, t_data *data, int i)
{
    char    *before;
    char    *path;
    char    *var;


    before = ft_substr(cmd, 0, i);
    var = search_dico(ft_substr(cmd, i + 1, ft_strchars_i(&cmd[i + 1], "|$?~%^{}: \"\'")), data);
    printf("var : <%c>\n", cmd[i + 1]);
    if (before)
        path = ft_strdup(before);
    if(!var && cmd[i + 1] == '?')
    {
        var = ft_itoa(s_error);
        path = ft_strjoin(path, var);
        path = ft_strjoin(path, &cmd[i + 2]);
        free (var);
        free (before);
        return (path);    
    }
    else
        path = ft_strjoin(before, var);
    if (ft_strchars_i(&cmd[i + 1], "|$?~%^${}: \"") != -1)
        path = ft_strjoin(path, &cmd[i + ft_strchars_i(&cmd[i + 1], "|$?~%^${}: \"")]);
    return (path);   
}

char    *expand_vars(char *cmd, t_data *data)
{
    int	simple_q;
	int	double_q;
    int i;
    int k;

    k = 0;
    i = 0;
    simple_q = 0;
    double_q = 0;
    while (cmd[i])
    {
        simple_q = (simple_q + (!double_q && cmd[i] == '\'')) % 2 ;
        double_q = (double_q + (!simple_q && cmd[i] == '\"')) % 2 ;
        if (!simple_q && cmd[i] == '$' && cmd[i + 1] && ((ft_strchars_i(&cmd[i + 1], "|~$%^{}: \"")
         && double_q) || (ft_strchars_i(&cmd[i + 1], "~$%^{}: ") && !double_q)))
        {
            cmd = sub_var(cmd, data, i);
            i = i * k  - (1 * k) + ft_strchars_i(&cmd[i], "|?~%$^{}: \"");
            if (ft_strchars_i(&cmd[i], "|?~%$^{}: \"") && i < 0)
                i++;
            k = 1;
        }
        else
            i++;
    }
    return (cmd);  
}

// char    **expand_all(char **cmd, t_data *data)
// {
//     int i;
    
//     i = 0;
//     while (cmd[i])
//     {
//         cmd[i] = expand_vars(cmd[i], data);
//         cmd[i] = expand_path(cmd[i], data);
//         i++;
//     }
//     return (cmd);
// }

char    *expand_all2(char *cmd, t_data *data)
{

    cmd = expand_vars(cmd, data);
    cmd= expand_path(cmd, data);
    return (cmd);
}