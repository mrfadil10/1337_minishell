/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:35:44 by stemsama          #+#    #+#             */
/*   Updated: 2023/06/01 19:24:57 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR 1

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <time.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct env
{
	char		*name;
	char		*value;
	char		*n_v;
	struct env	*next;
}	t_env;

typedef struct s_data
{
	int		ac;
	char	**av;
	char	**commands;
	char	*str;
}	t_data;

//-----------------------------------------------> implement_cd:

int		execute_cd(t_env **env, char **argv);
char	*get_path(t_env **env, char **argv);
char	*get_value(t_env **env, char *name);
void	go_to_home(t_env **env);
int		upd_oldpwd(t_env **env, char *pwd);

//-----------------------------------------------> implement_env:
t_env	*execute_env(t_env **env);
t_env	*creat_env(char **env);

//-----------------------------------------------> implement_pwd:
void	execute_pwd(t_env **env);

//-----------------------------------------------> implement_echo:
int		execute_echo(char **argv);
void	pars_echo(char **argv, int *is_n, int *i);

//-----------------------------------------------> implement_exit:
int		execute_exit(char **argv);
int		ft_isnumber(char *str);

//-----------------------------------------------> implement_export:
int		*execute_export(t_env **env, char **argv);
int		pars_export(char *av);
void	go_to_export(t_env **env, char *argv);

//-----------------------------------------------> implement_unset:
void	execute_unset(char **argv);

//-----------------------------------------------> tools1:
void	ft_lstadd_back2(t_env **lst, t_env *new);
t_env	*ft_lstnew_ind2(char *content);
char	*get_name(char *str);
char	*get_value1(char *str);
t_env	*sort_env(t_env **env);

//-----------------------------------------------> tools2:
int		is_builting(char **cmd);
void	go_to_execve(t_env **lst_env, char **cmd, char **env);
void	go_to_builting(char **cmd, t_env *lst_env);

//-----------------------------------------------> handler_signals:
int		sig_nals(void);
void	go_to_sigint(int sig);
void	go_to_sigquit(int sig);

//-----------------------------------------------> parsing:
void	parsing(t_data *parameter);
char	**split_case(char *str, char c);
char	*ft_strldup(const char *s, int lnt);
int		arg_token_lnt(char *str, char c);
int		arg_counter(char *str);
int		char_strlen(char *str, char c);

#endif
