/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:11:15 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/06 15:28:28 by amontalb         ###   ########.fr       */
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

char    *expand_path(char *cmd, t_data *data)
{

    
}

char    *expand_vars(char *cmd, t_data *data)
{


    
}

char    **expand_all(char **cmd, t_data *data)
{
    int i;
    
    i = 0;
    while (cmd[i])
    {
        cmd[i] = expand_vars(cmd[i], data);
        cmd[i] = expand_path(cmd[i], data);
        i++;
    }


}