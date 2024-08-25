/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:31:40 by mbirou            #+#    #+#             */
/*   Updated: 2024/08/25 19:32:28 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

void	ms_quote_hider(t_cmd *cmd, char **arg)
{
	int		has_pair;
	int		index;
	char	target_quote;

	index = -1;
	has_pair = 0;
	target_quote = -4;
	while (arg[0][++index])
	{
		if ((target_quote == -4 && (arg[0][index] == '\''
				|| arg[0][index] == '"')) || arg[0][index] == target_quote)
		{
			if (has_pair)
				target_quote = -4;
			else
				target_quote = arg[0][index];
			if (has_pair)
				has_pair --;
			else
				has_pair ++;
			arg[0][index] = (char)(-1 - (arg[0][index] == '\''));
		}
	}
	if (has_pair)
		ms_handle_errors(cmd, BAD_QUOTE, MS_SYNTAX_ERROR, NULL);
}

void	ms_hide_quotes(t_cmd *cmd)
{
	int	arg_i;

	while (cmd)
	{
		arg_i = -1;
		while (cmd->args[++arg_i])
			ms_quote_hider(cmd, &cmd->args[arg_i]);
		cmd = cmd->next;
	}
}

void	ms_remove_hiders(t_cmd *cd, int ia)
{
	char	*tp_arg;
	int		i;

	while (cd)
	{
		ia = -1;
		cd->args = ms_remove_empty_chars(cd->args);
		while (cd->args[++ia])
		{
			i = -1;
			while (cd->args[ia] && cd->args[ia][++i])
			{
				if (cd->args[ia][i] < 32 && cd->args[ia - (ia >= 1)][0] != '<'
					&& cd->args[ia - (ia >= 1)][0] != '>')
				{
					tp_arg = ms_tripple_join(ft_substr(cd->args[ia], 0, i),
							&cd->args[ia][i + 1], "", 100);
					free(cd->args[ia]);
					cd->args[ia] = tp_arg;
					i --;
				}
			}
		}
		cd = cd->next;
	}
}
