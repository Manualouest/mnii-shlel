/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokeniser_env_modifs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 02:24:56 by mbirou            #+#    #+#             */
/*   Updated: 2024/05/23 18:59:36 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

int	ms_get_len_of_env(char *param)
{
	int	len;

	len = 0;
	while (param[len] && ((ms_is_symbol(param[len]) == ms_is_symbol(param[0])
				&& param[len] != ' ')))
		len ++;
	if (param[len] && len == 0 && param[0] == ' ')
		len ++;
	return (len);
}

int	ms_is_it_worth_modifying_params(char *param)
{
	if (!param || ft_strlen(param) == (size_t)ms_get_len_of_env(param))
		return (0);
	return (1);
}

void	ms_redo_next_param(t_params *param)
{
	int		start;
	int		len;
	char	*tp_char;

	start = ms_get_len_of_env(param->text);
	len = ft_strlen(param->text) - start;
	tp_char = ft_substr(param->text, start, len);
	free(param->text);
	param->text = tp_char;
}

static void	ms_setup_next(t_params *copy_params, t_params *prev)
{
	t_params	*tp_param;

	if (ft_strlen(copy_params->text) !=
		(size_t)ms_get_len_of_env(copy_params->text))
		ms_redo_next_param(copy_params);
	else
	{
		if (copy_params->next)
		{
			tp_param = copy_params->next;
			free(prev->next);
			prev->next = tp_param;
			free(copy_params->text);
			free(copy_params);
		}
		else
			prev->next = NULL;
	}
}

static void	ms_do_env_modif(t_params *copy_params, t_params *prev,
			t_env_handler *env)
{
	t_env_handler	*tp_env;
	char			*env_name;

	if (prev && prev->symbol == DOLLAR && copy_params->type == STRING
		&& copy_params->quote_level % 2 == 0)
		// && ms_is_it_worth_modifying_params(copy_params->text))
	{
		prev->symbol = NO_SYMBOL;
		prev->quote_level = copy_params->quote_level;
		prev->type = STRING;
		env_name = ft_substr(copy_params->text, 0,
			ms_get_len_of_env(copy_params->text));
		tp_env = env_find(env, env_name);
		free(env_name);
		free(prev->text);
		prev->text = ft_strdup(tp_env->info.content);
		ms_setup_next(copy_params, prev);
	}
}

void	ms_make_env_easier(t_params *main_params, t_command *command, char **envp)
{
	t_params		*copy_params;
	t_params		*tp_params;
	// t_params		*next_param;
	t_env_handler	*env;

	copy_params = main_params;
	tp_params = NULL;
	env = setup_env_struct(envp);
	while (copy_params != NULL)
	{
		ms_do_env_modif(copy_params, tp_params, env);
		if (copy_params->next == NULL && copy_params)
		{
			ms_trim_spaces(copy_params, 1, tp_params, command);
			break ;
		}
		tp_params = copy_params;
		copy_params = copy_params->next;
	}
	envclear(&env, free);
}
