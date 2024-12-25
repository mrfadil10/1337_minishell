/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:03:54 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 16:32:23 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*next_node2(t_data *data)
{
	if (!data)
		return (NULL);
	data = data->next;
	while (data && data->t_type != PIPE)
		data = data->next;
	if (!data)
		return (NULL);
	if (!(data->next))
		return (NULL);
	return (data->next);
}

int	fd1_fd2_norm4(t_data *node2, int *fd1)
{
	if (*fd1 != -2)
		close(*fd1);
	if (node2->next->next->av[0])
	{
		*fd1 = open_file(node2, node2->next->next->av[0], NULL);
		node2->next->next->t_type = FILEE;
	}
	else
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		return (-2);
	}
	return (0);
}

int	fd1_fd2(t_data	*node2, int *fd1, int *fd2)
{
	int	a;

	a = 0;
	while (node2->next)
	{
		if (fd1_fd2_norm1(node2, fd2, a) == -2)
			return (-2);
		a = 0;
		if (fd1_fd2_norm2(node2, fd2) == -2)
			return (-2);
		if (node2->t_type == PIPE)
			break ;
		a = fd1_fd2_norm3(node2, fd2, a);
		if (a == -2)
			return (-2);
		else if (node2->next->t_type == INFERIOR)
		{
			if (fd1_fd2_norm4(node2, fd1) == -2)
				return (-2);
		}
		if ((*fd2 == -1) || (*fd1 == -1) || (*fd2 == -42) || (*fd1 == -42))
			return (-2);
		node2 = node2->next;
	}
	return (0);
}

int	nbr_pipe(t_data	*data)
{
	int	i;

	i = 0;
	while (data)
	{
		if (data->t_type == PIPE)
			i++;
		data = data->next;
	}
	return (i);
}

int	choice(t_data	*data, t_env *lst_env, t_env *lst_exp, char **env)
{
	g_data.nd = data;
	if (choice_norm1(g_data.p, lst_env, env, data) == 1)
		return (close(g_data.outt), close(g_data.inn), 1);
	if (g_data.p == 0)
	{
		if (fd1_fd2(g_data.nd, &g_data.nd->in, &g_data.nd->out) == -2)
			return (close(g_data.outt), close(g_data.inn), 1);
		return (choice_norm12(lst_env, lst_exp, env));
	}
	if (choice_norm11(g_data.nd, lst_env, lst_exp, env) == 1)
		return (close(g_data.outt), close(g_data.inn), 1);
	if (g_data.pid != -1)
		waitpid(g_data.pid, &g_data.exit_status, 0);
	while (wait(NULL) != -1)
		;
	return (close(g_data.outt), close(g_data.inn), g_data.exit_status);
}
