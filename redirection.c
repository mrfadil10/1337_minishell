/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 00:34:58 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/08 16:26:40 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_data *node, char *cmd)
{
	int	fd;

	fd = -2;
	if (node->next->t_type == SUPERIOR)
		fd = open(cmd, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (node->next->t_type == ADD)
		fd = open(cmd, O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (node->next->t_type == HRDC)
		fd = open(cmd, O_CREAT | O_RDWR, 0777);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (-42);
	}
	if (node->next->t_type == INFERIOR)
		fd = open(cmd, O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de la redirection");
		return (-42);
	}
	return (fd);
}

int	out_redirection(t_data *node, int fd)
{
	node->out = dup(1);
	if (dup2(fd, 1) == -1)
	{
		perror("Erreur lors de la redirection");
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (node->out);
}

int	in_redirection(t_data *node, int fd)
{
	node->in = dup(0);
	if (dup2(fd, 0) == -1)
	{
		perror("Erreur lors de la redirection");
		close(fd);
		return (1);
	}
	close(fd);
	return (node->in);
}
