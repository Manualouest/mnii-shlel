/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:15:43 by mscheman          #+#    #+#             */
/*   Updated: 2024/05/23 14:15:43 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**heredoc_lst_to_tab(t_list *lst);

char	**ms_heredoc(char *limiter)
{
	t_list	*tab;
	char	**ret;
	char	*input;

	input = readline(HEREDOC_PROMPT);
	tab = NULL;
	while (input && ft_strncmp(input, limiter, ft_strlen(input)) != 0)
	{
		ft_lstadd_back(&tab, ft_lstnew(input));
		input = readline(HEREDOC_PROMPT);
	}
	if (input)
		free(input);
	input = NULL;
	ft_lstadd_back(&tab, ft_lstnew(input));
	ret = heredoc_lst_to_tab(tab);
	return (ret);
}

static char	**heredoc_lst_to_tab(t_list *lst)
{
	t_list	*tmp;
	char	**tab;
	int		i;

	i = ft_lstsize(lst);
	tab = ft_calloc(i, sizeof(char *));
	i = 0;
	while (lst)
	{
		tab[i] = lst->content;
		i++;
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	return (tab);
}
