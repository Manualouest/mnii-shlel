/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokeniser_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:48:35 by mbirou            #+#    #+#             */
/*   Updated: 2024/06/18 00:59:40 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

t_cmd	*ms_tokeniser_main(char *line, char **envp)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	ms_base_setup(cmd, line);
	if (envp)
		ms_setup_round_two(cmd, envp);
	else
	{
		ms_free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

void	ms_free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tp_cmd;

	while (cmd != NULL)
	{
		i = -1;
		if (cmd->args)
		{
			while (cmd->args[++i] != 0)
				free(cmd->args[i]);
			free(cmd->args[i]);
			free(cmd->args);
		}
		tp_cmd = cmd->next;
		free(cmd);
		cmd = tp_cmd;
	}
	cmd = NULL;
}
