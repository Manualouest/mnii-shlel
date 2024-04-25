/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokeniser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:19:20 by mbirou            #+#    #+#             */
/*   Updated: 2024/04/25 20:04:39 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

char	*ms_get_next_item(char *line, int *main_index, int quote)
{
	char	*item;
	int		start;
	int		type;
	int		i;

	i = *main_index;
	while (line[i] && line[i] == ' ' && quote == 0)
		i ++;
	start = i;
	if (ft_isalnum(line[i]))
		type = STRING;
	else
		type = SYMBOL;
	while (line[i] && (type == ft_isalnum(line[i])
		|| (quote == 1 ) || (quote == 2 && line[i - 1] != '$')) && !(quote == 0
			&& line[i] == "'"[0]) && !(quote == 0 && line[i] == '"')
		&& (quote == 0 || ((quote == 1 && line[i] != "'"[0])
			|| (quote == 2 && line[i] != '"'))))
		i ++;
	if ((line[i] == "'"[0] || line[i] == '"')
		&& i == start)
		i ++;
	item = ft_substr(line, start, (i - start));
	*main_index = i;
	return (item);
}

void	ms_head_to_next_pipe(char *line, int *main_index)
{
	int	i;

	i = *main_index;
	while(line[i] && line[i] != '|')
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
				break;
			else
				return (0);
		}
	}
	return (1);
}

int	ms_is_symbol(char c)
{
	if (c == "'"[0] || c == '"' || c == '<' || ft_strncmp(&c, "<<", 2) == 0
		|| c == '>' || ft_strncmp(&c, ">>", 2) == 0 || c == '$' || c == '/')
		return (1);
	return (0);
}

int	ms_is_not_symbol(int c)
{
	if (('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z')
		|| ('0' <= c && c <= '9')
		|| c == '?')
		return (1);
	return (0);
}
