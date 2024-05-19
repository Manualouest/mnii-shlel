/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structure_translator_main.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:11:10 by mbirou            #+#    #+#             */
/*   Updated: 2024/05/19 19:50:42 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

static char	*ms_get_command(t_command *command)
{
	char	*args;

	args = malloc(sizeof(char) * ft_strlen(command->cmd) + 1);
	args[0] = 0;
	ft_strlcpy(args, command->cmd, ft_strlen(command->cmd) + 1);
	return (args);
}

static int	ms_get_nb_param(t_params *main_params)
{
	t_params	*params;
	int			i;

	params = main_params;
	i = 0;
	while (params != NULL)
	{
		i ++;
		params = params->next;
	}
	return (i);
}

static char	**ms_translate_params(t_params *main_params, char *cmd)
{
	int			len;
	int			i;
	char		**args;
	t_params	*param;

	param = main_params;
	i = 0;
	len = ms_get_nb_param(main_params);
	args = malloc(sizeof(char *) * (len + 2));
	args[len + 1] = 0;
	args[0] = cmd;
	while (param != NULL && ++i <= len)
	{
		args[i] = malloc(sizeof(char) * (ft_strlen(param->text) + 1));
		ft_strlcpy(args[i], param->text, ft_strlen(param->text) + 1);
		param = param->next;
	}
	write(1, "\n", 1);
	return (args);
}

void	ms_translate_to_cmd(t_cmd *cmd, t_pipes *main)
{
	t_pipes	*cpy_pipe;
	t_cmd	*cpy_cmd;

	cpy_pipe = main;
	cpy_cmd = cmd;
	while (cpy_pipe != NULL)
	{
		cpy_cmd->fd_in = 0;
		cpy_cmd->fd_out = 0;
		if (cpy_pipe->error != NO_ERROR)
			cpy_cmd->error_id = cpy_pipe->error;
		else
			cpy_cmd->error_id = cpy_pipe->command->error;
		cpy_cmd->args = ms_translate_params(cpy_pipe->command->params,
				ms_get_command(cpy_pipe->command));
		cpy_cmd->pid = 0;
		if (cpy_pipe->right)
			cpy_cmd->next = malloc(sizeof(*cpy_cmd));
		else
			cpy_cmd->next = NULL;
		if (cpy_cmd->next)
			cpy_cmd = cpy_cmd->next;
		cpy_pipe = cpy_pipe->right;
	}
}
