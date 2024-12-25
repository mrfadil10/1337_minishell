/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:35:44 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 17:23:19 by mfadil           ###   ########.fr       */
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
# define FILEE 9

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <time.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/ioctl.h>

typedef struct s_data
{
	int				pipe[2];
	int				t_type;
	int				sp;
	int				ac;
	int				in;
	int				out;
	char			**av;
	char			*commands;
	struct s_data	*prev;
	struct s_data	*next;
}	t_data;

typedef struct globv
{
	int			signal;
	int			heredoc;
	int			exit;
	int			hrdc_sig_c;
	int			atoi_exit;
	int			cheek;
	int			outt;
	int			inn;
	pid_t		pid;
	int			p;
	int			exit_status;
	int			flag;
	char		*name;
	t_data		*old;
	t_data		*nd;
}	t_globv;

extern t_globv			g_data;

typedef struct env
{
	int			tag;
	int			tag2;
	int			tag3;
	char		*name;
	char		*value;
	char		*n_v;
	struct env	*next;
}	t_env;

int			main_norm1(char **env, t_env *lst_env, t_env *lst_exp);
int			handler_exit_status(int exit_status);
int			child_status(int exit_status);
t_env		*ft_lstnew_ind3(char *content);
t_env		*creat_env2(char **env);

//-----------------------------------------------> pipes:
t_data		*next_node2(t_data *data);

//-----------------------------------------------> redirection:
int			out_redirection(t_data *node, int fd);
int			in_redirection(t_data *data, int fd);
int			open_file(t_data *node, char *cmd, char **name);

//-----------------------------------------------> redirection:
int			fd1_fd2(t_data	*node2, int *fd1, int *fd2);
int			nbr_pipe(t_data	*data);
int			choice(t_data	*data, t_env *lst_env, t_env *lst_exp, char **env);

//-----------------------------------------------> implement_cd:
int			execute_cd(t_env **env, char **argv);
char		*get_path(t_env **env, char **argv);
char		*get_value(t_env **env, char *name);
void		go_to_home(t_env **env);
int			upd_oldpwd(t_env **env, char *pwd);

//-----------------------------------------------> implement_env:
int			execute_env(t_env **env, char **cmd);
t_env		*creat_env(char **env);

//-----------------------------------------------> implement_pwd:
int			execute_pwd(t_env **env);

//-----------------------------------------------> implement_echo:
int			execute_echo(char **argv, t_env *lst_env);
void		pars_echo(char **argv, int *is_n, int *i);
char		*delete_quote(char *str);//new

//-----------------------------------------------> implement_exit:
int			execute_exit(char **argv);
int			ft_isnumber(char *str);

//-----------------------------------------------> implement_export:
int			execute_export(t_env **exp, t_env **env, char **argv);
int			pars_export(char *av);
int			go_to_export(t_env **exp, t_env **env, char *argv);
int			check_existe(t_env **env, char *new, int flag);
void		affiche_export(t_env **env);

//-----------------------------------------------> implement_unset:
int			execute_unset(t_env *env, t_env *exp, char **cmd);
int			go_to_unset(t_env *env, t_env *exp, char *cmd);
int			pars_unset(char *av);

//-----------------------------------------------> tools1:
void		ft_lstadd_back2(t_env **lst, t_env *new);
t_env		*ft_lstnew_ind2(char *content);
char		*get_name(char *str);
char		*get_value1(char *str);
t_env		*sort_env(t_env **env);

//-----------------------------------------------> tools2:
int			is_builting(char **cmd);
int			go_to_execve(t_env **lst_env, char **cmd, char **env);
int			go_to_builtin(char **cmd, t_env *lst_env, t_env *lst_exp);
char		*passe_sep(char *argv, char sep);
char		*passe_sep2(char *argv, char sep);

//-----------------------------------------------> tools3:
void		plus_equal_exist(t_env **exp, char *argv);
void		equal(t_env **exp, char *argv);
void		plus_equal_exist_env(t_env **env, char *argv);
void		equal_env(t_env **exp, char *argv);

//-----------------------------------------------> tools4:
int			ft_lstsize2(t_data *lst);
int			ft_atoi2(char *str);
int			ft_atoi_trois2(void);
int			ft_ispath(char *str);
void		execute_export_norm_1(char **argv, t_env *cur);

//-----------------------------------------------> tools6:
int			go_to_export_norm(t_env **exp, t_env **env, char *argv);
void		go_to_execve_norm2(char **cmd, char **env);
void		go_to_execve_norm1(t_env **lst_env, char **cmd, char **env);
int			fd1_fd2_norm1(t_data *node2, int *fd2, int a);
int			fd1_fd2_norm2(t_data *node2, int *fd2);

//-----------------------------------------------> tools7:
int			fd1_fd2_norm3(t_data *node2, int *fd2, int a);
void		go_to_execve_nprm3(char	**all_path, char **cmd, char **env);
int			choice_norm1(int p, t_env *lst_env, char **env, t_data	*data);
void		choice_norm2(t_data *node, int *fd1, int *fd2);
int			choice_norm3(t_data *node, int outt, int inn);

//-----------------------------------------------> tools8:
int			choice_norm4(t_data *node, t_env *lst_env, char **env);
int			choice_norm5(t_data *node, t_env *lst_env, \
			char **env, t_env *lst_exp);
int			choice_norm6(t_data *node, t_env *lst_env, \
			char **env, t_env *lst_exp);
void		choice_norm7(t_data *node);
void		choice_norm8(t_data *node);

//-----------------------------------------------> tools9:
void		choice_norm9(t_data *data);
int			choice_norm10(t_env *lst_env, t_env *lst_exp, char **env);
int			choice_norm11(t_data *node, t_env *lst_env, \
			t_env *lst_exp, char **env);
int			choice_norm12(t_env *lst_env, t_env *lst_exp, char **env);
int			open_file_norm1(t_data *node, char *cmd, \
			char **name, int fd);

//-----------------------------------------------> tools10:
int			check_unset(t_env *env, char **cmd);
char		*get_path_norm1(t_env **env, char **cmd);
int			upd_oldpwd_norm1(t_env **env, char *pwd);
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

//-----------------------------------------------> parsing_tools:
void		put_back(t_data **data, char *str, int t_type, int lnt);
t_data		*ft_mylstlast(t_data *list);
t_data		*new_data(t_data *prev, char *str, int t_type);
char		*type_strdup(const char *src);

//-----------------------------------------------> expand:
int			get_index(char *str);
int			get_lnt(char *str);
char		*get_var_value(char *str, char **env);
char		*insert(char *str1, char *str2, int size, int index);
char		*get_line(char *line, char **env, int idx);

//-----------------------------------------------> herdc_exp:
int			herdoc_expander(t_data *node, char **env, int fd1, char *name);
int			hrdc(t_data	*node2, int *fd1, char **env);

//-----------------------------------------------> utils:
void		*back_alloc(unsigned long lnt, int type);
char		*type_substr(const char *str, unsigned int start,
				size_t lnt);

//-----------------------------------------------> check_syntax:
//-----------------------------------------------> check_syntax_utils:

t_data		*normalize(t_data *data);
char		**ft_tabjoin(char **s1, char **s2);
void		tab_concat(t_data *node, t_data *data);
int			ft_tablen(char **str);
char		**dup_to_tab(char **str);
t_data		*ft_dup(t_data *data);
void		add_back(t_data **node, t_data *data);
char		*ft_mystrjoin(char *s1, char *s2);
char		**tab_fixed(char **str);
void		expand(t_data *data, t_env *lst_env);
char		*delete_one(char *str, int idx, int c);
void		handle_quotes(t_data *data);
int			part_of_delete_quote(t_data *data, int i, int *j);
char		**list_to_tab(t_env *lst_env);

//-------------------------------------------------------------> garbage collec

void		*ft_malloc(size_t size);
void		ft_free(void *ptr);
void		ft_exit(int status);
char		**ft_mysplit(char const *s, char c);
char		*ft_myitoa(int n);
char		*ft_readline(char *prompt);
char		*ft_mystrtrim(char const *s1, char const *set);

//# define malloc(size)	ft_malloc(size)
//# define free(ptr)	ft_free(ptr)
//# define exit(status)	ft_exit(status)

#endif