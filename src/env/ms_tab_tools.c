/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tab_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:20:59 by mscheman          #+#    #+#             */
/*   Updated: 2024/08/25 18:58:52 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**tab_append(char **tab, char *add, int pos)
{
	char	**dup;
	int		i;

	i = 0;
	if (pos == -1)
		pos = tablen(tab);
	dup = malloc(sizeof(char *) * (tablen(tab) + 2));
	while (tab[i])
	{
		if (i == pos)
			dup[i] = add;
		else
			dup[i] = tab[i - (i > pos)];
		i++;
	}
	if (i == pos)
		dup[i] = add;
	else
		dup[i] = tab[i - (i > pos)];
	dup[i + 1] = NULL;
	free(tab);
	return (dup);
}

void	tab_replace(char **tab, char *old, char *new)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == old)
		{
			free(tab[i]);
			tab[i] = new;
		}
		i++;
	}
}

char	**tab_clone(char **tab)
{
	char	**dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(char *) * (tablen(tab) + 1));
	while (tab[i])
	{
		dup[i] = ft_strdup(tab[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

char	*envp_find(char **envp, char *name)
{
	int	i;
	int	name_len;

	i = 0;
	while (envp[i])
	{
		name_len = 0;
		while (envp[i][name_len] && envp[i][name_len] != '=')
			name_len++;
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0
			&& (int)ft_strlen(name) == name_len)
			return (envp[i]);
		i++;
	}
	return (NULL);
}
