/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mathieu.petru@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:18:20 by LeCoqBeau         #+#    #+#             */
/*   Updated: 2023/11/11 14:50:15 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	size_t	i;

	dup = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dup)
		return (0);
	i = 0;
	while (ft_strlen(src) > i)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}
