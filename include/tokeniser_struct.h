/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:07:16 by mbirou            #+#    #+#             */
/*   Updated: 2024/08/18 04:58:33 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISER_STRUCT_H
# define TOKENISER_STRUCT_H

# define MS_FAIL_STRUCT "failed to create malloc mniishlel's struct"
# define MS_SYNTAX_ERROR "syntax error near unexpected token"
# define MS_FAIL_HEREDOC "here-document delimited by end-of-file"
# define MS_FILE_HEREDOC "failed to create temporary file for heredoc"

typedef enum e_cmd_errors
{
	NO_ERROR,
	BAD_QUOTE = 2,
	BAD_FILE = 3,
}	t_cmd_errors;

typedef struct s_cmd
{
	int				fd_in;
	int				fd_out;
	t_cmd_errors	error_id;
	char			**args;
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*first;
}					t_cmd;

#endif