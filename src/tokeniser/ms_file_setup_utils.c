/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_setup_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:59:36 by mbirou            #+#    #+#             */
/*   Updated: 2024/06/21 21:51:32 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

int	ms_is_file_real(char *filename)
{
	DIR	*dir;
	int	fd;

	if (filename[0] == -1 && (filename[1] == '<' || filename[1] == '>'))
		return (-3);
	if (!filename)
		return (-2);
	dir = opendir(&filename[(filename[0] < 0)]);
	if (dir)
	{
		closedir(dir);
		return (-1);
	}
	fd = open(&filename[(filename[0] < 0)], O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	return (0);
}

char	**ms_remove_filename(char **args, int elem_index)
{
	int		index;
	char	**nargs;

	index = -1;
	nargs = ft_calloc(sizeof(char *), tablen(args) - 1);
	while (args[++index])
	{
		if (index != elem_index && index != elem_index + 1)
			nargs[index - ((index > elem_index) * 2)] = args[index];
		else
			free(args[index]);
	}
	free(args);
	return (nargs);
}

int	ms_opens(t_cmd *cmd, char *filename, int is_created, int kind)
{
	if (kind == 1)
	{
		if (is_created == 0)
			return (open(filename, O_CREAT | O_APPEND | O_WRONLY, S_IRWXU));
		else if (is_created == 1)
			return (open(filename, O_APPEND | O_WRONLY));
		else
			ms_handle_errors(cmd, BAD_FILE, MS_SYNTAX_ERROR, filename);
		return (-1);
	}
	else if (kind == 0)
	{
		if (is_created == 0)
			return (open(filename, O_CREAT | O_WRONLY, S_IRWXU));
		else if (is_created == 1)
			return (open(filename, O_WRONLY));
		else
			ms_handle_errors(cmd, BAD_FILE, MS_SYNTAX_ERROR, filename);
		return (-1);
	}
	if (is_created)
		return (open(filename, O_RDONLY));
	else
		ms_handle_errors(cmd, BAD_FILE, MS_SYNTAX_ERROR, filename);
	return (-1);
}

void	ms_handle_errors(t_cmd *cmd, int error_id, char *error, char *token)
{
	if (cmd)
		cmd->error_id = error_id;
	write(2, error, ft_strlen(error));
	if (error_id > 0)
	{
		write(2, " '", 2);
		if (token)
			write(2, token, ft_strlen(token));
		else
			write(2, "newline", 7);
		write(2, "'", 1);
	}
	write(2, "\n", 1);
}
