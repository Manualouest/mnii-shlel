/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd_pre_execheck.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 04:01:12 by mbirou            #+#    #+#             */
/*   Updated: 2024/05/15 06:12:03 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	ms_check_syntax(t_command *command)
{
	int			i;
	t_params	*tp_params;

	tp_params = command->params;
	if (tp_params == NULL)
		return (EMPTY_ARG);
	while (tp_params)
	{
		i = -1;
		while (tp_params->text[++i])
			if (tp_params->text[i] == ' ' && i > 0)
				return (TOO_MANY_ARGUMENT);
		tp_params = tp_params->next;
	}
	return (NO_ERROR);
}

char	*ms_recreate_dir_path(t_command *command)
{
	char		*full_path;
	char		*tp_path;
	t_params	*tp_params;

	tp_params = command->params;
	full_path = NULL;
	tp_path = NULL;
	while (tp_params != NULL)
	{
		tp_path = malloc((ft_strlen(full_path)
					+ ft_strlen(tp_params->text) + 1) * sizeof(char));
		if (!tp_path)
			return (NULL);
		tp_path[0] = 0;
		ft_strlcpy(tp_path, full_path, ft_strlen(full_path) + 1);
		tp_path = ft_strncat(tp_path, tp_params->text,
				ft_strlen(tp_params->text));
		if (full_path)
			free(full_path);
		full_path = malloc((ft_strlen(tp_path) + 1) * sizeof(char));
		ft_strlcpy(full_path, tp_path, ft_strlen(tp_path) + 1);
		free(tp_path);
		tp_params = tp_params->next;
	}
	return (full_path);
}

void	ms_cd_pre_parsing(t_command *command)
{
	DIR		*open_test;
	char	*full_path;
	int		syntax_error;

	syntax_error = ms_check_syntax(command);
	if (syntax_error == 0)
		command->error = syntax_error;
	full_path = ms_recreate_dir_path(command);
	open_test = opendir(&full_path[1]);
	free(full_path);
	if (open_test == NULL)
		command->error = errno + 6;
	closedir(open_test);
}
