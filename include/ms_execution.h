/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:44:31 by mscheman          #+#    #+#             */
/*   Updated: 2024/05/18 14:44:54 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXECUTION_H
# define MS_EXECUTION_H

# define HEREDOC_PROMPT "\033[1;36mheredco > \033[0;0m"

typedef struct s_cmd
{
	int				fd_in;
	int				fd_out;
	char			**args;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

void	ms_exec(t_cmd *to_exec, char **envp, t_env_handler *path);
char	**ms_format_envp(t_env_handler *env);

char	**ms_heredoc(char *limiter);

# define HEREDOC_WARNING "mnii shlel: warning: here-document delimited by EOF"

t_cmd	*cmd_new(char **content);
void	cmd_add_back(t_cmd **cmd, t_cmd *new);
void	cmd_clear(t_cmd **cmd, void (*del)(void **));
void	cmd_iter(t_cmd *cmd, void (*f)(t_cmd *));

void	ms_exec_initfds(t_cmd *cmd);
void	ms_exec_redirectupdate(t_cmd *cmd, int infile, int outfile);
void	ms_exec_closefds(t_cmd *cmd);

#endif