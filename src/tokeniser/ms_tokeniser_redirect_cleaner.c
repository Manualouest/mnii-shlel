/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokeniser_redirect_cleaner.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:23:21 by mbirou            #+#    #+#             */
/*   Updated: 2024/05/23 18:51:56 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

void	ms_trim_get_start_lenght(int *start, int *length, int way,
			t_params *param)
{
	int	s;
	int	l;

	s = *start;
	l = *length;
	while (param->text[s] && param->text[s] == ' ' && s <= l && way == 10)
		s += way / 10;
	while (l > 0 && param->text[l - 1] && param->text[l - 1] == ' ' && s == 0)
		l -= way % 10;
	*start = s;
	*length = l;
}

void	ms_trim_spaces(t_params *param, int way, t_params *prev_param,
			t_command *command)
{
	int		s;
	int		l;
	char	*tp_char;

	s = 0;
	l = (int)ft_strlen(param->text);
	ms_trim_get_start_lenght(&s, &l, way, param);
	if (s < l)
	{
		tp_char = ft_substr(param->text, s, l);
		free(param->text);
		param->text = tp_char;
		free(tp_char);
	}
	else
	{
		free(param->text);
		if (prev_param)
			prev_param->next = param->next;
		else
			command->params = param->next;
		free(param);
	}
}

void	trim_redirect_spaces(t_command *command)
{
	t_params	*copy_params;
	t_params	*prev_param;

	copy_params = command->params;
	prev_param = NULL;
	while (copy_params)
	{
		if (copy_params->next && copy_params->symbol >= INPUT
			&& copy_params->symbol <= APPEND
			&& copy_params->next->type == STRING && copy_params->next->text)
		{
			prev_param = copy_params;
			ms_trim_spaces(copy_params->next, 10, prev_param, command);
		}
		if (copy_params->next && copy_params->next->symbol >= INPUT
			&& copy_params->next->symbol <= APPEND
			&& copy_params->type == STRING && copy_params->text)
			ms_trim_spaces(copy_params, 1, prev_param, command);
		prev_param = copy_params;
		copy_params = copy_params->next;
	}
}
