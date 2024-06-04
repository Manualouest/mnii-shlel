/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:08:02 by mscheman          #+#    #+#             */
/*   Updated: 2024/04/26 01:06:51 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENV_HANDLER_H
# define MS_ENV_HANDLER_H

typedef int	t_bool;

typedef struct s_env_str
{
	char	*name;
	char	*content;
}	t_env_str;

typedef struct s_env_handler
{
	t_env_str				info;
	struct s_env_handler	*next;
}	t_env_handler;

t_env_handler	*setup_env_struct(char **envp);

t_env_handler	*env_new(t_env_str content);
void			envadd_back(t_env_handler **env, t_env_handler *new);
void			envclear(t_env_handler **env, void (*del)(void *));
void			envdelone(t_env_handler *env, void (*del)(void *));
void			enviter(t_env_handler *env, void (*f)(t_env_handler *));

t_env_str		ms_string_to_env(char *info, int sep);
t_env_handler	*env_find(t_env_handler *env, char *name);
t_env_handler	*env_replace(t_env_handler **env, t_env_handler *new,
					t_env_handler *old);

#endif
