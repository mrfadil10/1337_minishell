/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:03:54 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/08 16:30:33 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_globv	g_data;

t_data	*next_node2(t_data *data)
{
	if (!data)
		return (NULL);
	data = data->next;

	while (data &&  data->t_type != COMMND)
		data = data->next;
	if (!data)
		return (NULL);
	return (data);
}
int hrdc(t_data	*node2, int *fd1, int *fd2)
{
	ft_putstr_fd("2 fyhdty\n",2);
	t_data *node;
	node = node2;
	while (node->next)
	{
		if (node->t_type == PIPE)
			break ;
		if (node->t_type == HRDC)
		{
			if (*fd1 != -2)
				close(*fd1);
			*fd1 = open_file(node, node->next->next->av[0]);
			node->next->next->t_type = FILEE;
		}
		if ((*fd2 == -1) || (*fd1 == -1) || (*fd2 == -42) || (*fd1 == -42))
			return -2;
		node = node->next;
	}
	return (0);
}
			//dup2(node->pipe[0], 0);
			//close(node->pipe[0]);
			//return (0);

int fd1_fd2(t_data	*node2, int *fd1, int *fd2)
{
	ft_putstr_fd("1 fyhdty\n",2);
	hrdc(node2, fd1, fd2);
	while (node2->next)
	{
		if (node2->t_type == PIPE)
			break;
		if (node2->next->t_type == SUPERIOR || node2->next->t_type == ADD)
		{
			if (*fd2 != -2)
				close(*fd2);
			*fd2 = open_file(node2, node2->next->next->av[0]);
			node2->next->next->t_type = FILEE;
		}
		else if (node2->next->t_type == INFERIOR)
		{
			if (*fd1 != -2)
				close(*fd1);
			*fd1 = open_file(node2, node2->next->next->av[0]);
			node2->next->next->t_type = FILEE;
		}
		//if (node2->t_type == HRDC)
		//{
		//	dup2(node2->pipe[0], 0);
		//	close(node2->pipe[0]);
		//	return (0);
		//}
		if ((*fd2 == -1) || (*fd1 == -1) || (*fd2 == -42) || (*fd1 == -42))
			return -2;
		node2 = node2->next;
	}
	return (0);
}

int nbr_pipe(t_data	*data)
{
	int i = 0;
	while (data)
	{
		if (data->t_type == PIPE)
			i++;
		data = data->next;
	}
	return (i);
}

void choice(t_data	*data, t_env *lst_env, t_env *lst_exp, char **env)
{
	t_data	*node;
	t_data	*old;
	pid_t	pid;
	int		p;
	(void) env;

	p = nbr_pipe(data);
	old = NULL;
	node = data;
	// if (p >= 500)
	// {
	// 	ft_putstr_fd("fork: Resource temporarily unavailable\n", 2);
	// 	return ;
	// }
	if (p == 0)
	{
		if (is_builting(node->av))
		{
			go_to_builting(node->av, lst_env, lst_exp);
			return;
		}
		else
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				return ;
			}
			else if (pid == 0)
			{
				go_to_execve(node, &lst_env, node->av, env);
				return;
			}
			while (wait(NULL) != -1)
			;
			return;
		}
	}
	while (node)
	{
		node->out = -2;
		node->in = -2;
		if (p != 0)
			pipe(node->pipe);
		if (old != NULL)
				node->in = old->pipe[0];
		if (p != 0)
			node->out = node->pipe[1];
		if (fd1_fd2(node, &node->in, &node->out) == -2)
			return ;
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return ;
		}
		else if (pid == 0)
		{
			// signal(SIGQUIT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (node->in != -2)
			{
				dup2(node->in , 0);
				close(node->in);
			}
			if (node->out != -2)
			{
				// printf("--> %d :\n", node->out);
				dup2(node->out , 1);
				close(node->out);
			}
			if (p != 0)
			{
				close(node->pipe[0]);
				close(node->pipe[1]);
				if (old)
					close(old->in);
			}
			if (is_builting(node->av))
			{
				go_to_builting(node->av, lst_env, lst_exp);
				exit(1);
			}
			else
				go_to_execve(node, &lst_env, node->av, env);
		}
		if (p != 0)
			close(node->pipe[1]);
		if (old != NULL)
			close(old->pipe[0]);
		old = node;
		if (node->next)
			node = next_node2(node);
		else
			break;
		p--;
		}
		while (wait(NULL) != -1)
			;
}
