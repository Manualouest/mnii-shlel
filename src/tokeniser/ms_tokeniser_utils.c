/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokeniser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:19:20 by mbirou            #+#    #+#             */
/*   Updated: 2024/05/21 20:41:45 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

int	ms_is_line_done(char *line, int i, char *item)
{
	while (i <= (int)ft_strlen(line) && line[i] != 0)
	{
		if (line[i] != ' ')
			return (0);
		i ++;
	}
	if (ft_strlen(item) > 0)
		return (0);
	return (1);
}

void	ms_head_to_next_pipe(char *line, int *main_index)
{
	int	i;

	i = *main_index;
	while (i <= (int)ft_strlen(line) && line[i] && line[i] != '|')
		i ++;
	*main_index = i + 1;
}

int	ms_am_i_at_the_next_pipe(char *line, int i)
{
	while (--i > 0)
	{
		if (line[i] != ' ')
		{
			if (line[i] == '|')
				break ;
			else
				return (0);
		}
	}
	return (1);
}

int	ms_is_symbol(char c)
{
	if (c == "'"[0] || c == '"' || c == '<'
		|| c == '>' || c == '$')
		return (1);
	return (0);
}
