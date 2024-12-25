/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:08:04 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 16:16:47 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	g_data.exit = 1;
}

int	sig_nals(void)
{
	void	*sig1;
	void	*sig2;

	sig1 = signal(SIGINT, go_to_sigint);
	sig2 = signal(SIGQUIT, SIG_IGN);
	if (sig1 == SIG_ERR || sig2 == SIG_ERR)
		printf("Signal Error\n");
	return (1);
}
