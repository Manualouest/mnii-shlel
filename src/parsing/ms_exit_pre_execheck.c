/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit_pre_execheck.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 06:30:13 by mbirou            #+#    #+#             */
/*   Updated: 2024/05/15 06:39:24 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

void	ms_exit_pre_parsing(t_command *command)
{
	int	i;

	if (command->params && command->params->next)
		command->error = TOO_MANY_ARGUMENT;
	i = -1;
	if (command->params->type != STRING && command->error == NO_ERROR)
		command->error = BAD_PARAM;
	while (command->params->text && command->params->text[++i]
		&& command->error == NO_ERROR)
	{
		if (command->params->text[i] == ' ')
			command->error = TOO_MANY_ARGUMENT;
		if (!ft_isdigit(command->params->text[i])
			&& command->params->text[i] != ' ')
			command->error = BAD_PARAM;
	}
}
