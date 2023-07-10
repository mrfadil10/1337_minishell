/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:35:44 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/10 22:46:29 by mfadil           ###   ########.fr       */
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
# include <fcntl.h>
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
	int				genre;
	int				sp;
	int				ac;
	char			**av;
	char			*commands;
	char			*str;
	struct s_data	*prev;
	struct s_data	*next;
}	t_data;

//-----------------------------------------------> implement_cd:

int			execute_cd(t_data **env, char **argv);
char		*get_path(t_data **env, char **argv);
char		*get_value(t_data **env, char *name);
void		go_to_home(t_data **env);
int			upd_oldpwd(t_data **env, char *pwd);

//-----------------------------------------------> implement_env:
t_data		*execute_env(t_data **env);
t_data		*creat_env(char **env);

//-----------------------------------------------> implement_pwd:
void		execute_pwd(t_data **env);

//-----------------------------------------------> implement_echo:
int			execute_echo(char **argv);
void		pars_echo(char **argv, int *is_n, int *i);

//-----------------------------------------------> implement_exit:
int			execute_exit(char **argv);
int			ft_isnumber(char *str);

//-----------------------------------------------> implement_export:
int			*execute_export(t_data **env, char **argv);
int			pars_export(char *av);
void		go_to_export(t_data **env, char *argv);

//-----------------------------------------------> implement_unset:
void		execute_unset(char **argv);

//-----------------------------------------------> tools1:
void		ft_lstadd_back2(t_data **lst, t_data *new);
t_data		*ft_lstnew_ind2(char *content);
char		*get_name(char *str);
char		*get_value1(char *str);
t_data		*sort_env(t_data **env);

//-----------------------------------------------> tools2:
int			is_builting(char **cmd);
void		go_to_execve(t_data **lst_env, char **cmd, char **env);
void		go_to_builting(char **cmd, t_data *lst_env);

//-----------------------------------------------> handler_signals:
int			sig_nals(void);
void		go_to_sigint(int sig);
void		go_to_sigquit(int sig);

//-----------------------------------------------> parsing:
void		parsing(t_data *parameter);
int			arg_token_lnt(char *str, char c);
int			arg_counter(char *str);
int			char_strlen(char *str, char c);
void		remove_token(char **argv);
void		set_arguments(int ac, char **av, char *str);
char		**is_command(char *str, t_data *parameter);
char		*type_substr(const char *str, unsigned int start,
				int type, size_t lnt);
t_collect	*type_lstnew(void *content);
void		*back_alloc(unsigned long lnt, int type);
void		put_back(t_data **data, char *str, int genre, int lnt);
t_data		*new_data(t_data *prev, char *str, int genre);
t_data		*ft_mylstlast(t_data *list);
void		type_lstadd_back(void *ptr, int type);

#endif
