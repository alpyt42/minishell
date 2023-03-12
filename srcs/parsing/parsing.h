/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 01:28:05 by ale-cont          #+#    #+#             */
/*   Updated: 2023/03/12 23:17:17 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../includes/minishell.h"

char	**ft_cmdsplit(char *cmd, char *s);
char	**cmdlexing(char *cmd);
int		check_pars(char *cmd, t_data *data);
char	**expand_all(char **cmd, t_data *data);
char	*expand_all2(char *cmd, t_data *data);
int		launch_mini(t_data *data, char *cmd);
char	*ft_strim_quotes(char *s);
t_list	*fill_nodes(char **cmds, t_data *data);
t_node	*get_out1(t_node *node, char **cmds, int *i, t_data *data);
t_node	*get_out2(t_node *node, char **cmds, int *i, t_data *data);
t_node	*get_in1(t_node *node, char **cmds, int *i, t_data *data);
t_node	*get_in2(t_data *data, t_node *node, char **cmds, int *i);

#endif