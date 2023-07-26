/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:35:44 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/25 16:09:15 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE 0
# define ERROR 1
# define SUPERIOR 2
# define INFERIOR 3
# define SIQUOTE 4
# define DOQUOTE 5
# define COMMND 6
# define ADD 7
# define HRDC 8

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <time.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_collect
{
	void				*data;
	struct s_collect	*next;
}	t_collect;

typedef struct globv
{
	t_collect	*tmp;
	t_collect	*end;
	int			signal;
	int			heredoc;
	int			exit;
}	t_globv;

extern t_globv			g_data;

typedef struct env
{
	char		*name;
	char		*value;
	char		*n_v;
	struct env	*next;
}	t_env;

typedef struct s_data
{
	int				pipe[2];
	int				t_type;
	int				sp;
	int				ac;
	char			**av;
	char			*commands;
	struct s_data	*prev;
	struct s_data	*next;
}	t_data;

//-----------------------------------------------> implement_cd:
int			execute_cd(t_env **env, char **argv);
char		*get_path(t_env **env, char **argv);
char		*get_value(t_env **env, char *name);
void		go_to_home(t_env **env);
int			upd_oldpwd(t_env **env, char *pwd);

//-----------------------------------------------> implement_env:
t_env		*execute_env(t_env **env);
t_env		*creat_env(char **env);

//-----------------------------------------------> implement_pwd:
void		execute_pwd(t_env **env);

//-----------------------------------------------> implement_echo:
int			execute_echo(char **argv);
void		pars_echo(char **argv, int *is_n, int *i);
char		*delete_quote(char *str);//new

//-----------------------------------------------> implement_exit:
int			execute_exit(char **argv);
int			ft_isnumber(char *str);

//-----------------------------------------------> implement_export:
int			*execute_export(t_env **exp, t_env **env, char **argv);
int			pars_export(char *av);
void		go_to_export(t_env **exp, t_env **env, char *argv);
int			check_existe(t_env **env, char *new);
void		affiche_export(t_env **env);

//-----------------------------------------------> implement_unset:
int			*execute_unset(char **cmd);

//-----------------------------------------------> tools1:
void		ft_lstadd_back2(t_env **lst, t_env *new);
t_env		*ft_lstnew_ind2(char *content);
char		*get_name(char *str);
char		*get_value1(char *str);
t_env		*sort_env(t_env **env);

//-----------------------------------------------> tools2:
int			is_builting(char **cmd);
void		go_to_execve(t_env **lst_env, char **cmd, char **env);
void		go_to_builting(char **cmd, t_env *lst_env, t_env *lst_exp);
char		*passe_sep(char *argv, char sep);
char		*passe_sep2(char *argv, char sep);

//-----------------------------------------------> tools3:
void		plus_equal_exist(t_env **exp, char *argv);
void		equal(t_env **exp, char *argv);
void		plus_equal_exist_env(t_env **env, char *argv);
void		equal_env(t_env **exp, char *argv);

//-----------------------------------------------> handler_signals:
int			sig_nals(void);
void		go_to_sigint(int sig);
void		go_to_sigquit(int sig);

//-----------------------------------------------> parsing:
int			check_sep(char *sep, char s);
void		rep_sp(char *str);
void		token_str(t_data **data, char **str, int *lnt);
void		token_quotes(t_data **data, char **str, int *lnt);
void		token_redirect(t_data **data, char **str, int *lnt);
t_data		*tokenize(char *line);
int			is_closed(char *str, int type);
int			error_sup_inf(int t_type, int next);
int			error_pipe_hrdc_add(int t_type, int next);
int			lexer(t_data *data, char **env);
t_data		*parsing(char *line, char **env);

//-----------------------------------------------> n'existe pas !!!!!!!!!!!!! :
int			arg_token_lnt(char *str, char c);
int			arg_counter(char *str);
int			char_strlen(char *str, char c);
void		remove_token(char **argv);
void		set_arguments(int ac, char **av, char *str);
char		**is_command(char *str, t_data *parameter);
int			pars_quote(char *line);

//-----------------------------------------------> parsing_tools:
void		put_back(t_data **data, char *str, int t_type, int lnt);
t_data		*ft_mylstlast(t_data *list);
t_data		*new_data(t_data *prev, char *str, int t_type);
char		*type_strdup(const char *src, int type);

//-----------------------------------------------> expand:
int			get_index(char *str);
int			get_lnt(char *str);
char		*get_var_value(char *str, char **env);
char		*insert(char *str1, char *str2, int size, int index);
char		*get_line(char *line, char **env, int idx);
void		herdoc_expander(t_data *node, char **env);

//-----------------------------------------------> utils:
t_collect	*type_lstlast(t_collect *lst);
t_collect	*type_lstnew(void *content);
void		type_lstadd_back(void *ptr, int type);
void		*back_alloc(unsigned long lnt, int type);
char		*type_substr(const char *str, unsigned int start,
				int type, size_t lnt);

//-----------------------------------------------> utils_2:
void		free_all(int fd);

//-----------------------------------------------> check_syntax:
//-----------------------------------------------> check_syntax_utils:

t_data	*normalize(t_data *data);
char	**ft_tabjoin(char **s1, char **s2);
void	tab_concat(t_data *node, t_data *data);
int		ft_tablen(char **str);
char	**dup_to_tab(char **str);
t_data	*ft_dup(t_data *data);
void	add_back(t_data **node, t_data *data);
char	*ft_mystrjoin(char *s1, char *s2);

#endif