/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:04:18 by mscheman          #+#    #+#             */
/*   Updated: 2024/04/25 19:09:55 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void export_no_args(t_env_handler *env);

int	builtin_export(t_env_handler *env, char **name, char **content)
{
	int				i;
	t_env_handler	*tmp;

	i = 0;
	tmp = NULL;
	if (!name && !content && env != NULL)
	{
		enviter(env, export_no_args);
		return (0);
	}
	if (!env || !name || !*name || !content || !*content)
	while (name[i])
	{

	}
	return (0);
}

static void export_no_args(t_env_handler *env)
{
	printf("declare -x %s=%s\n", env->info.name, env->info.content);
}

static