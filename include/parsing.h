/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:03:14 by mbirou            #+#    #+#             */
/*   Updated: 2024/05/15 06:31:25 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <string.h>

# include <mnii_shlel.h>

void	ms_parsing_main(t_pipes *main);
void	ms_cd_pre_parsing(t_command *command);
void	ms_unset_pre_parsing(t_command *command);
void	ms_exit_pre_parsing(t_command *command);

#endif