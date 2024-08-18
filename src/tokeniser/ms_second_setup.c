/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_second_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:20:40 by mbirou            #+#    #+#             */
/*   Updated: 2024/08/18 07:53:16 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

int	ms_get_var_start(char *arg, int *var_len)
{
	int	quote_level;
	int	i;
	int	is_num;

	quote_level = 0;
	i = -1;
	while (arg[++i])
	{
		quote_level = ms_change_quote_level(arg, i, quote_level);
		if (quote_level % 2 == 0 && arg[i] == '$')
		{
			if (!arg[i + 1] || arg[i + 1] == ' ' || (arg[i + 1] < 0 && !ms_change_quote_level(arg, i + 1, quote_level))
				|| arg[i + 1] == '"' || arg[i + 1] == '\'' || arg[i + 1] == '=')
				continue ;
			if (ms_change_quote_level(arg, i + 1, 0) != 0)
				return (i);
			if (arg[i + 1] == '?')
			{
				*var_len = 2;
				return (i);
			}
			is_num = 0;
			if (ft_isdigit(arg[i + 1]))
				is_num = 1;
			while (arg[++*var_len + i] && (!is_num || *var_len != 2
					|| (is_num && !ft_isdigit(arg[*var_len + i])))
				&& (ft_isalnum(arg[*var_len + i]) || arg[*var_len + i] == '_'))
				;
			return (i);
		}
	}
	return (-1);
}

char *ms_get_var(char *arg, int var_pos, int var_len, char **envp)
{
	char	*var_name;
	char	*raw_content;
	char	*var_content;

	if (var_pos == -1)
		return (NULL);
	if (var_len >=0 )
		var_name = ft_substr(arg, var_pos + 1, var_len);
	else
		var_name = ft_calloc(sizeof(char), 1);
	if (!var_name)
		return (NULL);
	if (var_name[0] == 0)
		return (var_name);
	if (var_name[0] == '?')
	{
		var_content = ft_itoa(g_signal);
		free(var_name);
		return (var_content);
	}
	else 
		raw_content = envp_find(envp, var_name);
	free(var_name);
	if (!raw_content)
	{
		raw_content = ft_calloc(sizeof(char), 1);
		return (raw_content);
	}
	var_content = ft_strdup(&(ft_strchr(raw_content, '=')[1]));
	return(var_content);
}

int	ms_insert(char **arg, char *var_content, int var_pos, int *var_len)
{
	char	*arg_start;
	char	*new_arg;
	int		content_lenght;

	if (var_pos >= 0)
		arg_start = ft_substr(arg[0], 0, var_pos);
	else
		arg_start = ft_calloc(sizeof(char), 1);
	if (!arg_start)
		return (0);
	content_lenght = ft_strlen(var_content);
	if (*var_len > 0)
		new_arg = ms_tripple_join(arg_start, var_content, &arg[0][var_pos + *var_len + 1], 110);
	else
		new_arg = ms_tripple_join(arg_start, var_content, &arg[0][var_pos + 1], 110);
	*var_len = content_lenght;
	if (!new_arg)
		return (0);
	free(arg[0]);
	arg[0] = new_arg;
	return (1);
}

char	ms_get_quote_to_index(char *arg, int pos)
{
	int	i;
	int	quote_level;

	i = -1;
	quote_level = 0;
	while(arg[++i] && i <= pos)
		quote_level = ms_change_quote_level(arg, i, quote_level);
	if (quote_level == 1)
		return ((char)(-2));
	else if (quote_level == 2)
		return ((char)(-1));
	return (0);
}

char	*ms_replace_str(char *original, char *new)
{
	free(original);
	return (new);
}

int	ms_do_normal_separation(char ***arg, char *space, char quote, int arg_i)
{
	if (quote != 0)
		arg[0] = tab_append(arg[0], ms_tripple_join(&quote, ft_strdup(&space[1]), &quote, 10), arg_i + 1);
	else
		arg[0] = tab_append(arg[0], ft_strdup(&space[1]), arg_i + 1);
	arg[0][arg_i] = ms_replace_str(arg[0][arg_i], ft_substr(arg[0][arg_i], 0, ft_strlen(arg[0][arg_i]) - ft_strlen(space)));
	if (!arg[0][arg_i])
		return (0);
	return (1);
}

int	ms_get_var_pos(int var_pos, int action)
{
	static int	var_pos_save;

	if (action)
		var_pos_save = var_pos;
	return (var_pos_save);
}

void	ms_insert_spaced_loop(char ***arg, int arg_i, char *space, char quote)
{
	int	i;

	i = 0;
	while (space)
	{
		if (i == 0)
		{
			if (quote != 0)
				arg[0] = tab_append(arg[0], ms_tripple_join(&quote, ft_strdup(&space[1]), "\0", 10), arg_i + 1);
			else
				arg[0] = tab_append(arg[0], ft_strdup(&space[1]), arg_i + 1);
			arg[0][arg_i] = ms_replace_str(arg[0][arg_i], ft_substr(arg[0][arg_i], 0, ft_strlen(arg[0][arg_i]) - ft_strlen(space)));
		}
		else
			ms_do_normal_separation(arg, space, quote, arg_i);
		space = ft_strrchr(&arg[0][arg_i][ms_get_var_pos(0, 0)], ' ');
		i ++;
	}
}

int	ms_insert_spaced(char ***arg, int arg_i, int var_pos, int content_lenght)
{
	char	quote;
	char	*space;
	char	*tp_space;
	int		i;

	quote = ms_get_quote_to_index(arg[0][arg_i], var_pos);
	if (!arg[0][arg_i])
		return (0);
	i = 0;
	space = ft_strchr(&arg[0][arg_i][var_pos], ' ');
	while (space && ft_strlen(space) > ft_strlen(&arg[0][arg_i][var_pos + content_lenght]))
	{
		tp_space = space;
		space = ft_strchr(&tp_space[1], ' ');
	}
	space = tp_space;
	// ms_insert_spaced_loop(arg, arg_i, space, quote);
	// ms_get_var_pos(var_pos, 1);
	while (space)
	{
		if (i == 0)
		{
			if (quote != 0)
				arg[0] = tab_append(arg[0], ms_tripple_join(&quote, ft_strdup(&space[1]), "\0", 10), arg_i + 1);
			else
				arg[0] = tab_append(arg[0], ft_strdup(&space[1]), arg_i + 1);
			arg[0][arg_i] = ms_replace_str(arg[0][arg_i], ft_substr(arg[0][arg_i], 0, ft_strlen(arg[0][arg_i]) - ft_strlen(space)));
		}
		else
			ms_do_normal_separation(arg, space, quote, arg_i);
		space = ft_strrchr(&arg[0][arg_i][var_pos], ' ');
		i ++;
	}
	arg[0][arg_i] = ms_replace_str(arg[0][arg_i], ft_strjoin(arg[0][arg_i], &quote));
	return (1);
}

void	ms_setup_var_info(char ***args, int index, int *var_pos, int *var_len)
{
	*var_len = 0;
	*var_pos = ms_get_var_start(args[0][index], var_len);
	*var_len -= 1;
}

int	ms_expand_loop(char ***args, char **envp)
{
	int		index;
	int		var_pos;
	int		var_len;
	char	*var;

	index = -1;
	while (args[0][++index])
	{
		if (ms_has_dollar(args[0][index]))
		{
			ms_setup_var_info(args, index, &var_pos, &var_len);
			var = ms_get_var(args[0][index], var_pos, var_len, envp);
			if (!var)
				return (0);
			if (ft_strchr(var, ' ') && ms_insert(&args[0][index],
				var, var_pos, &var_len) && !ms_insert_spaced(args,
				index, var_pos, var_len))
				return (0);
			else if (!ms_insert(&args[0][index], var, var_pos, &var_len))
				return (0);
			if (ms_has_dollar(args[0][index]))
				index --;
		}
	}
	return (1);
}

void	ms_setup_round_two(t_cmd *cmd, char **envp)
{
	t_cmd		*cpy_cmd;

	cpy_cmd = cmd;
	ms_separate_symbols_base(cmd);
	while (cpy_cmd)
	{
		cpy_cmd->args = ms_remove_empty_chars(cpy_cmd->args);
		if (!ms_expand_loop(&cpy_cmd->args, envp))
		{
			ms_handle_errors(NULL, 0, MS_FAIL_STRUCT, NULL);
			ms_free_cmd(cmd);
			return ;
		}
		cpy_cmd = cpy_cmd->next;
	}
	ms_in_out_files_setup(cmd, envp);
	ms_remove_hiders(cmd, -1);
}
