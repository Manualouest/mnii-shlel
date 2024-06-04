/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:05:06 by mscheman          #+#    #+#             */
/*   Updated: 2024/05/01 17:05:06 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

static void	unset_delete(t_env_handler *env, t_env_handler *del);

int	builtin_unset(t_env_handler *env, char **names)
{
	int				i;
	t_bool			success;
	t_env_handler	*old;

	i = 0;
	old = NULL;
	success = true;
	if (!names || !*names)
		return (EXIT_FAILURE);
	while (names[i])
	{
		old = env_find(env, names[i]);
		if (!old)
			success = false;
		else
		{
			unset_delete(env, old);
			envdelone(old, free);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	unset_delete(t_env_handler *env, t_env_handler *del)
{
	t_env_handler	*tmp;

	tmp = env;
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
}
