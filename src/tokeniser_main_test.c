/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_main_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:08:02 by mbirou            #+#    #+#             */
/*   Updated: 2024/04/26 22:44:29 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

void	ms_pipe_test_printer(t_pipes *full_line);

int	main()
{
	
	char	*a;
	char	*path;
	int		size;
	t_pipes	*full_line;

	size = 2147483647;
	path = malloc(sizeof(char) * size);
	path = getcwd(path, size);
	if (!path)
	{
		write(1, "path is too long\n", 17);
		exit(0);
	}
	write(1, "~", 1);
	write(1, path, ft_strlen(path));
	a = readline(" what_da_shell $ ");
	if (a && a != NULL)
	{
		full_line = ms_tokeniser_main(a);
		ms_pipe_test_printer(full_line);
		ms_pipes_free_main(full_line);
	}
	free(path);
	free(a);
	return (0);
}

void	ms_pipes_test_printer_find_cmd(int cmd)
{
	if (cmd == 0)
		write(1, ": NO_CMD", 8);
	else if (cmd == 1)
		write(1, ": ECHO", 6);
	else if (cmd == 2)
		write(1, ": CD", 4);
	else if (cmd == 3)
		write(1, ": PWD", 5);
	else if (cmd == 4)
		write(1, ": EXPORT", 8);
	else if (cmd == 5)
		write(1, ": UNSET", 7);
	else if (cmd == 6)
		write(1, ": ENV", 5);
	else if (cmd == 7)
		write(1, ": EXIT", 6);
}

void	ms_pipes_test_printer_find_error(int cmd)
{
	if (cmd == 0)
		write(1, ": NO_ERROR", 10);
	else if (cmd == 1)
		write(1, ": BAD_PARAMS", 12);
	else if (cmd == 2)
		write(1, ": BAD_CMD", 9);
	else if (cmd == 3)
		write(1, ": BAD_PATH", 10);
}

void	ms_pipes_test_printer_find_symbol(int symbol)
{
	if (symbol == 0)
		write(1, "NO_SYMBOL", 9);
	else if (symbol == 1)
		write(1, "QUOTE", 5);
	else if (symbol == 2)
		write(1, "DOUBLE_QUOTE", 12);
	else if (symbol == 3)
		write(1, "INPUT", 5);
	else if (symbol == 4)
		write(1, "HEREDOC", 7);
	else if (symbol == 5)
		write(1, "REDIRECT", 8);
	else if (symbol == 6)
		write(1, "APPEND", 6);
	else if (symbol == 7)
		write(1, "DOLLAR", 6);
}

void	ms_pipe_test_printer(t_pipes *full_line)
{
	int			is_done;
	t_params	*tp_params;

	is_done = 0;
	while (is_done != 1)
	{
		if (full_line->command == NULL)
			write(1, "command = NULL\n", 15);
		else
		{
			write(1, "command = not NULL\n", 19);
			write(1, &(char){full_line->command->builtins + '0'}, 1);
			ms_pipes_test_printer_find_cmd(full_line->command->builtins);
			write(1, "\n", 1);
			write(1, full_line->command->cmd, ft_strlen(full_line->command->cmd));
			write(1, "\n", 1);
			write(1, &(char){full_line->command->has_option + '0'}, 1);
			write(1, "\n", 1);
			write(1, &(char){full_line->command->error + '0'}, 1);
			ms_pipes_test_printer_find_error(full_line->command->error);
			write(1, "\n", 1);
			write(1, "params:", 7);
			if (full_line->command->params)
			{
				write(1, "\n", 1);
				tp_params = full_line->command->params;
				while (tp_params != NULL)
				{
					write(1, "		quote level: ", 15);
					write(1, &(char){tp_params->quote_level + '0'}, 1);
					write(1, "\n", 1);
					write(1, "		type: ", 8);
					if (tp_params->type == 0)
						write(1, "symbol", 6);
					else
						write(1, "STRING", 6);
					write(1, "\n", 1);
					write(1, "		text: |", 9);
					if (tp_params->type == 1)
						write(1, tp_params->text, ft_strlen(tp_params->text));
					else
						write(1, "NULL", 4);
					write(1, "|\n", 2);
					write(1, "		symbol: ", 10);
					ms_pipes_test_printer_find_symbol(tp_params->symbol);
					write(1, "\n", 1);
					write(1, "		________________________\n", 27);
					tp_params = tp_params->next;
				}
			}
			else
				write(1, " NULL\n", 6);
			write(1, "________________________\n", 25);
		}
		if (full_line->right == NULL)
		{
			write(1, "right = NULL\n", 13);
			is_done = 1;
		}
		else
		{
			write(1, "right = pipe\n", 13);
			full_line = full_line->right;
		}
	}
}
