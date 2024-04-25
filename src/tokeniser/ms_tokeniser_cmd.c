/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokeniser_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:11:46 by mbirou            #+#    #+#             */
/*   Updated: 2024/04/25 20:04:29 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

int	ms_find_command(char *line, int *i)
{
	char	*command;
	int		cmd;

	command = ms_get_next_item(line, i, 0);
	// write(1, command, ms_strlen(command));
	if (ft_strncmp(command, "echo", 4) == 0)
		cmd = ECHO;
	else if (ft_strncmp(command, "cd", 2) == 0)
		cmd = CD;
	else if (ft_strncmp(command, "pwd", 3) == 0)
		cmd = PWD;
	else if (ft_strncmp(command, "export", 6) == 0)
		cmd = EXPORT;
	else if (ft_strncmp(command, "unset", 5) == 0)
		cmd = UNSET;
	else if (ft_strncmp(command, "env", 3) == 0)
		cmd = ENV;
	else if (ft_strncmp(command, "exit", 4) == 0)
		cmd = EXIT;
	else
		cmd = NO_CMD;
	free(command);
	return (cmd);
}

void	ms_init_cmd(t_command *command, char *line, int *i)
{
	command->cmd = ms_find_command(line, i);
	command->params = malloc(sizeof(*command->params));
	command->params->quote_level = 0;
	command->has_option = 0;
	if (command->cmd == ECHO && line[*i] != 0
		&& line[*i + 1] != 0 && line[*i + 1] == '-'
		&& line[*i + 2] != 0 && line[*i + 2] == 'n'
		&& ((line[*i + 3] != 0 && line[*i + 3] == ' ') || line[*i + 3] == 0))
	{
		command->has_option = 1;
		*i = *i + 3;
	}
	command->error = 0;
}
