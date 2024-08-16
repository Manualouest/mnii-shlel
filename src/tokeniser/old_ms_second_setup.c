/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_ms_second_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:00:56 by mbirou            #+#    #+#             */
/*   Updated: 2024/08/15 19:41:54 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

char	*ms_setup_env(char *tp_env, char **arg, int env_start, int env_len)
{
	char	*env;
	char	*new_arg;
	int		index;

	index = -1;
	while (tp_env && tp_env[++index] && tp_env[index] != '=')
		;
	env = ft_substr(tp_env, index + 1, ft_strlen(tp_env));
	if (ft_strlen(env) == 0)
	{
		free(env);
		env = ft_calloc(sizeof(char), 1);
	}
	else
		env = ms_tripple_join(&(char){-1}, env, &(char){-1}, 10);
	new_arg = ms_tripple_join(ft_substr(arg[0], 0, env_start),
			ft_substr(env, 0, ft_strlen(env)),
			ft_strdup(&arg[0][env_start + env_len]), 111);
	if (env)
		free(env);
	if (arg[0])
		free(arg[0]);
	return (new_arg);
}

int	ms_env_util(char **arg, int *index, int *len)
{
	int	quote_level;

	quote_level = 0;
	while (arg[0][++*index])
	{
		--*index;
		while (arg[0][++*index] && arg[0][*index] != '$')
			quote_level = ms_change_quote_level(arg[0], *index, quote_level);
		if (quote_level != 1)
			break ;
	}
	if (quote_level == 1)
	{
		*index = -1;
		*len = -1;
		// printf("left\n");
		return (0);
	}
	// printf("|%s|, %c, %d, %d, %d\n", arg[0], arg[0][*len + *index], quote_level, *len, *index);
	while (arg[0][++*len + *index] && arg[0][*len + *index] != ' '
		&& arg[0][*len + *index] != '$' && arg[0][*len + *index] > 0
		&& arg[0][*len + *index] != '='
		&& (arg[0][*len + *index] != '"' && arg[0][*len + *index] != '\''
		&& quote_level == 0))
	{
		// printf("|%s|, %c, %d, %d, %d\n", arg[0], arg[0][*len + *index], quote_level, *len, *index);
		if (*len > 1 && arg[0][(*len - 1) + *index] == '?')
			break ;
	}
	if (arg[0][*len + *index] != '"' || arg[0][*len + *index] != '\''
		|| arg[0][*len + *index] > 0)
	{
		if (quote_level == 0)
			arg[0][*len + *index - 1] = arg[0][*len + *index];
		else
			*len = *len -1;
	}
	// printf("%d\n", *len);
	return (1);
}

char	**ms_split_env(char **env, char **args, int env_index, char quote)
{
	char	**cut_env;
	char	**n_args;
	int		cut_i;
	int		args_i;

	cut_env = ft_split(env[0], ' ');
	n_args = ft_calloc(sizeof(char *), tablen(cut_env) + tablen(args) + 1);
	cut_i = 0;
	args_i = -1;
	while (args_i - cut_i < tablen(args) && args[++args_i - cut_i])
	{
		if (args_i != env_index)
			n_args[args_i - (args_i > env_index)] = args[args_i - cut_i];
		else
		{
			free(args[args_i]);
			cut_i --;
			while (cut_env[++cut_i] && ++args_i > 0)
				n_args[args_i - 1] = ms_tripple_join(&quote,
						&cut_env[cut_i][(cut_env[cut_i][0] < 0)], &quote, 0);
		}
	}
	free_tab((void **)cut_env);
	free(args);
	return (n_args);
}

void	ms_do_env(char **arg, char **envp, char ***args, int env_index)
{
	int		index;
	int		env_len;
	char	*env_name;
	char	*env_content;

	index = -1;
	env_len = 0;
	if (!ms_env_util(arg, &index, &env_len))
		return ;
	env_name = ft_substr(arg[0], index + 1, env_len - 1);
	if (env_name[0] == '?')
	{
		free(env_name);
		env_name = ft_itoa(g_signal);
		env_content = ft_strjoin("=", env_name);
	}
	else
		env_content = ft_strdup(envp_find(envp, env_name));
	arg[0] = ms_setup_env(env_content, arg, index, env_len);
	if (ft_strchr(arg[0], ' ') != 0)
		args[0] = ms_split_env(arg, args[0], env_index, (char)(-3));
	free(env_content);
	free(env_name);
}

void	ms_setup_round_two(t_cmd *cmd, char **envp)
{
	int		args_i;
	t_cmd	*cpy_cmd;

	cpy_cmd = cmd;
	ms_separate_symbols_base(cmd);
	while (cpy_cmd)
	{
		args_i = -1;
		cpy_cmd->args = ms_remove_empty_chars(cpy_cmd->args);
		while (cpy_cmd->args[++args_i])
		{
			while (cpy_cmd->args && ms_has_dollar(cpy_cmd->args[args_i])
				&& ft_strncmp(cpy_cmd->args[args_i - (args_i > 0)], "<<", 2) != 0)
				ms_do_env(&cpy_cmd->args[args_i], envp, &cpy_cmd->args, //ms_do_env(&cpy_cmd->args[args_i], envp, &cpy_cmd->args,
					args_i);
			if (!cpy_cmd->args)
			{
				ms_free_cmd(cmd);
				return ;
			}
		}
		cpy_cmd = cpy_cmd->next;
	}
	ms_remove_hiders(cmd, -1);
	ms_in_out_files_setup(cmd, envp);
}
