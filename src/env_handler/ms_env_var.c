/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:07:29 by mscheman          #+#    #+#             */
/*   Updated: 2024/04/23 18:54:25 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *extract_env_name(char *var);

t_env_handler	*setup_env_struct(char **envp)
{
	int		i;
	char 	*tmp;

	i = 0;
	while (envp[i])
	{
		tmp = extract_env_name(envp[i]);
		printf("%s = %s\n", tmp, &tmp[ft_strlen(tmp) + 1]);
		free(tmp);
		i++;
	}
	return (NULL);
}

static char *extract_env_name(char *var)
{
	int		i;
	char	*work;

	i = -1;
	work = strdup(var);
	while (work[++i])
	{
		if (work[i] != '=')
			continue ;
		work[i] = 0;
		break ;
	}
	return (work);
}