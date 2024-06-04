/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:59 by mscheman          #+#    #+#             */
/*   Updated: 2024/05/01 17:00:59 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

void	builtin_env(t_env_handler *env)
{
	while (env)
	{
		printf("%s=%s\n", env->info.name, env->info.content);
		env = env->next;
	}
}
