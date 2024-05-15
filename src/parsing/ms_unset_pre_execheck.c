/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset_pre_execheck.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 05:53:08 by mbirou            #+#    #+#             */
/*   Updated: 2024/05/15 06:24:45 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

void	ms_unset_pre_parsing(t_command *command)
{
	t_params	*tp_params;
	int			i;

	tp_params = command->params;
	if (tp_params == NULL)
		command->error = EMPTY_ARG;
	while (tp_params != NULL)
	{
		i = -1;
		while (tp_params->text && tp_params->text[++i])
			if (ms_is_symbol(tp_params->text[i])
				|| (!ft_isalpha(tp_params->text[i])
					&& tp_params->text[i] != ' ' && tp_params->text[i] != '_'))
				command->error = BAD_PARAM;
		tp_params = tp_params->next;
	}
}
