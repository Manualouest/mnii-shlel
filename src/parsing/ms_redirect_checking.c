/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect_checking.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:41:06 by mbirou            #+#    #+#             */
/*   Updated: 2024/05/30 06:00:08 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static void	ms_move_args_front(char ***args, int i)
{
	int	ii;

	while (args[0][i])
	{
		
		write(1, "before : ", 9);
		ii = -1;
		while (args[0][++ii])
			
		free(args[0][i]);
		args[0][i] = NULL;
		// free(args[0][i]);
		if (args[0][i + 1])
		{
			args[0][i] = malloc(sizeof(char) * (ft_strlen(args[0][i + 1]) + 1));
			ft_strlcpy(args[0][i], args[0][i + 1], ft_strlen(args[0][i + 1]) + 1);
		}
		else
			args[0][i] = NULL;
		i ++;
	}
}

void	ms_input_handler(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i] && cmd->error_id == NO_ERROR)
	{
		if (ft_strncmp(cmd->args[i], "<", 1) == 0 && cmd->args[i + 1])
		{
			if (cmd->fd_in != -1)
				close(cmd->fd_in);
			cmd->fd_in = open(cmd->args[i + 1], O_RDONLY);
			if (cmd->fd_in == -1)
				cmd->error_id = BAD_INPUT;
			ms_move_args_front(&cmd->args, i + 1);
			ms_move_args_front(&cmd->args, i);
		}
		// write(1, cmd->args[i], ft_strlen(cmd->args[i]));
	}
	if (cmd->fd_in == -1)
		cmd->fd_in = 1;
}

void	ms_redirect_handler(t_cmd *cmd)
{
	int	i;

	i = -1;
	ms_input_handler(cmd);
	while (cmd->args[++i])
	{
		if (cmd->args[i][0] && 
			ft_strncmp(cmd->args[i], ">", 1) == 0 && cmd->args[i + 1])
		{
			if (ft_strncmp(cmd->args[i], ">>", 2) == 0)
			{
				if (cmd->fd_out != -1)
					close(cmd->fd_out);
				cmd->fd_out = open(cmd->args[i + 1], O_APPEND | O_CREAT);
			}
			else
			{
				if (cmd->fd_out != -1)
					close(cmd->fd_out);
				cmd->fd_out = open(cmd->args[i + 1], O_WRONLY | O_CREAT);
			}
		}
	}
	if (cmd->fd_out == -1)
		cmd->fd_out = 1;
}
