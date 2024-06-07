/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_initfds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:19:53 by mscheman          #+#    #+#             */
/*   Updated: 2024/05/27 12:35:19 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

void	ms_exec_initfds(t_cmd *cmd)
{
	int	pipes_fd[2];

	if (cmd->next == NULL)
		return ;
	pipe(pipes_fd);
	if (cmd->fd_out == STDOUT_FILENO)
		cmd->fd_out = pipes_fd[1];
	else
		close(pipes_fd[1]);
	if (cmd->next->fd_in == STDIN_FILENO)
		cmd->next->fd_in = pipes_fd[0];
	else
		close(pipes_fd[0]);
}

void	ms_exec_closefds(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
}
