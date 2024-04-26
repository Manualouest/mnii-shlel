/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokeniser_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:11:46 by mbirou            #+#    #+#             */
/*   Updated: 2024/04/26 22:45:05 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

char	*ms_get_next_item(char *line, int *main_index)
{
	char	*item;
	int		start;
	int		type;
	int		i;

	i = *main_index;
	while (line[i] && line[i] == ' ')
		i ++;
	start = i;
	if (ft_isalnum(line[i]))
		type = STRING;
	else
		type = SYMBOL;
	while (line[i] && (type == ft_isalnum(line[i])))
		i ++;
	item = ft_substr(line, start, (i - start));
	*main_index = i;
	return (item);
}

int	ms_find_command(char *line, int *i, t_command *struct_command)
{
	char	*command;
	int		cmd;

	command = ms_get_next_item(line, i);
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
	struct_command->cmd = command;
	return (cmd);
}

void	ms_init_cmd(t_command *command, char *line, int *i)
{
	command->builtins = ms_find_command(line, i, command);
	command->params = malloc(sizeof(*command->params));
	command->params->quote_level = 0;
	command->has_option = 0;
	if (command->builtins == ECHO && line[*i] != 0
		&& line[*i + 1] != 0 && line[*i + 1] == '-'
		&& line[*i + 2] != 0 && line[*i + 2] == 'n'
		&& ((line[*i + 3] != 0 && line[*i + 3] == ' ') || line[*i + 3] == 0))
	{
		command->has_option = 1;
		*i = *i + 3;
	}
	command->error = 0;
}
