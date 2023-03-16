/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 01:43:39 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/15 22:31:58 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../../includes/minishell.h"

void	*print_error(int type, char *cmd, char *arg, int error);
int		symbol_errors(char *error, int type, int *exit);
void	ft_free_dico(void *content);
void	ft_free_node(void *content);
void	*ft_free_mini(t_data *data);
char	**ft_append_tab(char **in, char *newstr);
int		len_tab(char **tab);
int		ft_strchars_i(const char *s, char *set);
char	**ft_replace_in_matrix(char **matrix, char **insert, int n);
char	**mini_split(char *str, int i, int j, int lenone);
int		pos_in_arr(char **arr, char *to_find, char set);
char	**sort_arr(char **arr);
void	display_cmd(t_list *cmds);
void	display_arr(char **arr, char *info);
t_list	*fill_struct_test(t_data *data);

#endif