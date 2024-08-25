/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:36:06 by mbirou            #+#    #+#             */
/*   Updated: 2024/08/25 18:59:45 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

void	ms_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 130;
	}
}

void	ms_swap_signal(int	*old_signal)
{
	int	tp_int;

	tp_int = *old_signal;
	*old_signal = g_signal;
	g_signal = tp_int;
}

void	ms_setup_signal(int error_id, char *error)
{
	if (!ft_strncmp(error, MS_SYNTAX_ERROR, ft_strlen(error)))
		g_signal = 2;
	else if (error_id == 13 || error_id == 2)
		g_signal = 1;
	else
		g_signal = 0;
}
