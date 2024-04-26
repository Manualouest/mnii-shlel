/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:04:18 by mscheman          #+#    #+#             */
/*   Updated: 2024/04/26 01:10:18 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void				export_no_args(t_env_handler *env);

int	builtin_export(t_env_handler *env, t_env_str *params)
{
	int				i;
	t_env_handler	*tmp;
	t_env_handler	*dup;

	i = -1;
	tmp = NULL;
	if (params == NULL && env != NULL)
	{
		enviter(env, export_no_args);
		return (EXIT_SUCCESS);
	}
	if (!env || !params || !params[0].name)
		return (INVALID_PARAMETERS);
	while (params[++i].name)
	{
		dup = env_find(env, params[i].name);
		tmp = env_new((t_env_str){params[i].name, params[i].content});
		if (!dup)
			envadd_back(&env, tmp);
		else
		{
			env_replace(&env, tmp, dup);
			envdelone(dup, free);
		}
	}
	return (EXIT_SUCCESS);
}

static void	export_no_args(t_env_handler *env)
{
	printf("declare -x %s=%s\n", env->info.name, env->info.content);
}