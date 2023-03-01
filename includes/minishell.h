/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:57:31 by ale-cont          #+#    #+#             */
/*   Updated: 2023/02/07 12:56:09 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** libraries
*/

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>

# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"
# define FD_READ 0
# define FD_WRITE 1

typedef struct s_data
{
	t_list	*cmds;
	t_list	*dico;
	char	**env;
	char	**argv;
	int		quit;
	int		quotes_hd;
	int		n_cmd;
	pid_t	*p_ids;
	int		pipa[2];
	int		pipb[2];
}			t_data;

typedef struct s_node
{
	char	**all_cmd;
	char	*all_path;
	int		infile;
	int		outfile;
}			t_node;

enum	e_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

//----------------------------------------builtins----
int		is_builtin(char *cmd);
int		built_exit(t_data *data);
int		built_export(t_data *data);
int		built_pwd(void);
int		built_echo(t_data *data);
int		built_cd(t_data *data);
int		built_unset(t_data *data);
//----------------------------------------env---------
void	init_dico(t_data *data);
char	*search_dico(char *search, t_data *data);
int		set_env_vars(t_data *data, char *glob_var, char *val);
char	*find_in_arr(char **arr, char *to_find);
void	display_data(t_data *data);
void	init_data(t_data *data);
int		get_here_doc(char *del, t_data *data);
//----------------------------------------exec--------
void	exec_cmd_path(char ***res, char *path, char *cmd, char **env);
int		errors(char *strerr, char *error, int n);
int		mini_process(t_data *data);
void	exec(t_data *data);
//----------------------------------------main--------
//----------------------------------------parsing-----
char	**ft_cmdsplit(char *cmd, char *s);
char	**cmdlexing(char *cmd);
char	*check_pars(char *cmd, t_data *data);
char    **expand_all(char **cmd, t_data *data);
char    *expand_all2(char *cmd, t_data *data);
int		launch_mini(t_data *data, char *cmd);
char	*ft_strim_quotes(char *s);
t_list	*fill_nodes(char **cmds, t_data *data);

t_node  *get_out1(t_node *node, char **cmds, int *i);
t_node  *get_out2(t_node *node, char **cmds, int *i);
t_node  *get_in1(t_node *node, char **cmds, int *i);
t_node  *get_in2(t_data *data, t_node *node, char **cmds, int *i);


//----------------------------------------prompt------
char	*get_prompt(t_data *data);
//----------------------------------------signals-----
void	signal_receive(int sig);
//----------------------------------------tools-------
//----------------------------------------utils-------
char	**ft_append_tab(char **in, char *newstr);
int		len_tab(char **tab);
int		ft_strchars_i(const char *s, char *set);
char	**ft_replace_in_matrix(char **matrix, char **insert, int n);
char	**mini_split(char *str, int i, int j, int lenone);
int		pos_in_arr(char **arr, char *to_find, char set);
//----------------------------------------debug-------
void	display_cmd(t_list *cmds);
void	display_arr(char **arr, char *info);
t_list	*fill_struct_test(t_data *data);
#endif