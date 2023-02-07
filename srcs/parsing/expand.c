/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:11:15 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/07 16:00:16 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// gerer :
//     ~
//     $ + PATH
//     $ + ?
//     $ + PATH mais faux;
    
//     stocker tout ce qui est abvant le $ puis aller jusquau signe separateur suivant et voir si ce qui est dans 
//     intervalle est un PATH ou pas.

// char    *expand_path(char *cmd, t_data *data)
// {
    
    
// }

char    *sub_var(char *cmd, t_data *data, int i)
{
    char    *before;
    char    *path;
    char    *var;


    before = ft_substr(cmd, 0, i);
    printf("before : <%s>\n", before);
    var = search_dico(ft_substr(cmd, i + 1, ft_strchars_i(&cmd[i + 1], "$?~%^{}: \"")), data);
    printf("var : <%s>\n", var);
    if(!var)
        path = ft_strdup(before);
    else
        path = ft_strjoin(before, var);
    printf("<<<%s>>>\n", path);
    printf("int : %d\n", ft_strchars_i(&cmd[i + 1], "$?~%^${}: \""));
    if(ft_strchars_i(&cmd[i + 1], "$?~%^${}: \"") != -1)
        path = ft_strjoin(path, &cmd[i + 1 + ft_strchars_i(&cmd[i + 1], "$?~%^${}: \"")]);
    printf("end : <<<%s>>>\n", path);
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
        double_q = (double_q + (!simple_q && cmd[i] == '\'')) % 2 ;
        if (!simple_q && cmd[i] == '$' && cmd[i + 1] && ft_strchars_i(&cmd[i + 1], "?~$%^{}: \""))
        {
            cmd = sub_var(cmd, data, i);
            printf("___%d\n", i);
            i = i * k  - (1 * k) + ft_strchars_i(&cmd[i], "?~%$^{}: \"");
            if (ft_strchars_i(&cmd[i], "?~%$^{}: \"") && i < 0)
                i++;
            k = 1;
            printf("___%d\n", i);
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
// }