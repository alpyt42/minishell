/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:15:17 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/11 20:15:52 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../includes/minishell.h"

void	init_dico(t_data *data);
char	*search_dico(char *search, t_data *data);
int		set_env_vars(t_data *data, char *glob_var, char *val);
char	*find_in_arr(char **arr, char *to_find);
void	display_data(t_data *data);
void	init_data(t_data *data);
int		get_here_doc(char *del, t_data *data);

#endif