/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_initfds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:19:53 by mscheman          #+#    #+#             */
/*   Updated: 2024/09/06 11:18:55 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

int	ms_setup_pipes(t_cmd *cmd)
{
	int	pipes_fd[2];

	while (cmd && cmd->next)
	{
		if (pipe(pipes_fd) == -1)
			return (EXIT_FAILURE);
		if (cmd->fd_out == STDOUT_FILENO)
			cmd->fd_out = pipes_fd[1];
		else if (pipes_fd[1] != -1)
			close(pipes_fd[1]);
		if (cmd->next->fd_in == STDIN_FILENO)
			cmd->next->fd_in = pipes_fd[0];
		else if (pipes_fd[0] != -1)
			close(pipes_fd[0]);
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}

void	ms_exec_closefds(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out != -1)
		close(cmd->fd_out);
	if (cmd->next)
		ms_exec_closefds(cmd->next);
}
