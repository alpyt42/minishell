/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:55:12 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/12 01:16:12 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../includes/minishell.h"

int	is_builtin(t_node *n);
int	built_exit(t_data *data, t_node *n);
int	built_export(t_data *data, t_node *n);
int	built_pwd(void);
int	built_echo(t_node *n);
int	built_cd(t_data *data, t_node *n);
int	built_unset(t_data *data, t_node *n);
int	built_env(t_data *d, int tri);

#endif