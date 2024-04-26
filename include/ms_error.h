/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:21:41 by mscheman          #+#    #+#             */
/*   Updated: 2024/04/25 23:15:47 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

typedef int t_bool;

# define TRUE 1
# define FALSE 0

typedef enum e_error
{
	INVALID_PARAMETERS = -1,
} t_error;

#endif
