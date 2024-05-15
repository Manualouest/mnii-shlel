/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_pre_execheck_main.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 04:05:51 by mbirou            #+#    #+#             */
/*   Updated: 2024/05/15 06:37:18 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

void	ms_check_pipes_and_quotes(t_pipes *main)
{
	t_pipes			*tp_main;
	t_params		*tp_params;
	t_cmd_errors	error_found;

	tp_main = main;
	error_found = NO_ERROR;
	while (tp_main != NULL)
	{
		if (tp_main->command->builtins == NO_CMD
			&& ft_strlen(tp_main->command->cmd) == 0)
			error_found = BAD_PIPE;
		if (tp_main->command->params != NULL)
		{
			tp_params = tp_main->command->params;
			while (tp_params->next != NULL)
				tp_params = tp_params->next;
			if (tp_params->quote_level != 0)
				error_found = BAD_QUOTE;
		}
		if (error_found != NO_ERROR)
			break ;
		tp_main = tp_main->right;
	}
	main->error = error_found;
}

void	ms_parsing_main(t_pipes *main)
{
	t_pipes	*tp_main;

	tp_main = main;
	ms_check_pipes_and_quotes(main);
	if (main->error != NO_ERROR)
		return ;
	while (tp_main != NULL)
	{
		if (tp_main->command->builtins == CD)
			ms_cd_pre_parsing(tp_main->command);
		// else if (tp_main->command->builtins == EXPORT)
		// 	
		else if (tp_main->command->builtins == UNSET)
			ms_unset_pre_parsing(tp_main->command);
		// else if (tp_main->command->builtins == ENV)
		// 	
		else if (tp_main->command->builtins == EXIT)
			ms_exit_pre_parsing(tp_main->command);
		tp_main = tp_main->right;
	}
}
