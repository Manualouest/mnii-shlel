/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:56:56 by mscheman          #+#    #+#             */
/*   Updated: 2024/05/23 16:14:17 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms_env_handler.h>

t_env_handler	*env_new(t_env_str content)
{
	t_env_handler	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (0);
	node->info = content;
	node->next = 0;
	return (node);
}

void	envadd_back(t_env_handler **env, t_env_handler *new)
{
	if ((*env) == NULL)
	{
		(*env) = new;
		return ;
	}
	if (new == NULL)
		return ;
	if ((*env)->next == NULL)
	{
		(*env)->next = new;
		return ;
	}
	envadd_back(&(*env)->next, new);
}

void	envclear(t_env_handler **env, void (*del)(void *))
{
	if (!env || !(*env) || !del)
		return ;
	if ((*env)->next)
		envclear((&(*env)->next), del);
	del((*env)->info.name);
	free(*env);
	*env = NULL;
}

void	envdelone(t_env_handler *env, void (*del)(void *))
{
	if (!env || !del)
		return ;
	del(env->info.name);
	free(env);
	env = NULL;
}

void	enviter(t_env_handler *env, void (*f)(t_env_handler *))
{
	if (env == NULL)
		return ;
	f(env);
	if (env->next != NULL)
		enviter(env->next, f);
}
