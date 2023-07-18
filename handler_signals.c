/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:08:04 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/07 12:53:23 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void go_to_sigint(int sig)
{
	// il ya les cas (heardoc & read & execution)
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void go_to_sigquit(int sig)
{
	if (sig == SIGQUIT)
		;
	printf("1\n");
	return;
}

int	sig_nals(void)
{
	void	*sig1;
	void	*sig2;

	sig1 = signal(SIGINT, go_to_sigint);
	sig2 = signal(SIGQUIT, go_to_sigquit);
	if (sig1 == SIG_ERR || sig2== SIG_ERR)
	{
		printf("Signal Error");
	}
	return (1);
}
