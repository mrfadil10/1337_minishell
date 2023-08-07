/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:08:04 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/07 10:10:08 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

void	go_to_sigint(int sig)
{
	(void) sig;
	if (waitpid(0, NULL, WNOHANG))
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	go_to_sigquit(int sig)
{
	if (sig == SIGQUIT)
		;
	printf("1\n");
	return ;
}

int	sig_nals(void)
{
	void	*sig1;
	void	*sig2;

	sig1 = signal(SIGINT, go_to_sigint);
	sig2 = signal(SIGQUIT, SIG_IGN);
	if (sig1 == SIG_ERR || sig2 == SIG_ERR)
	{
		printf("Signal Error");
	}
	return (1);
}
