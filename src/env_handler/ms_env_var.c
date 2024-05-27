/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:07:29 by mscheman          #+#    #+#             */
/*   Updated: 2024/04/26 13:10:39 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

static void			sort_envp(char **envp);
static t_env_str	extract_env_name(char *var);

t_env_handler	*setup_env_struct(char **envp)
{
	int				i;
	t_env_str		tmp;
	t_env_handler	*lst;

	i = 0;
	sort_envp(envp);
	while (envp[i])
	{
		tmp = extract_env_name(envp[i]);
		if (i == 0)
			lst = env_new(tmp);
		else
			envadd_back(&lst, env_new(tmp));
		i++;
	}
	return (lst);
}

static t_env_str	extract_env_name(char *var)
{
	int			i;
	t_env_str	ret;
	char		*work;

	i = -1;
	work = strdup(var);
	while (work[++i])
	{
		if (work[i] != '=')
			continue ;
		work[i] = 0;
		break ;
	}
	ret.name = work;
	ret.content = &work[i + 1];
	return (ret);
}

static void	sort_envp(char **envp)
{
	size_t	len;
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i] && envp[i + 1])
	{
//		printf("%d : %s\n\t%d : %s\n", i, envp[i], i + 1, envp[i + 1]);
		len = ft_strlen(envp[i]);
		if (len < ft_strlen(envp[i + 1]))
			len = ft_strlen(envp[i + 1]);
		if (ft_strncmp(envp[i], envp[i + 1], len) > 0)
		{
			tmp = envp[i];
			envp[i] = envp[i + 1];
			envp[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	builtin_env(t_env_handler *env)
{
	while (env)
	{
		printf("%s=%s\n", env->info.name, env->info.content);
		env = env->next;
	}
}
