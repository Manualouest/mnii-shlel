/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:32:41 by mscheman          #+#    #+#             */
/*   Updated: 2024/04/25 23:15:47 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <get_next_line_bonus.h>

# include <ms_env_handler.h>
# include <ms_error.h>
# include <ms_execution.h>

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <curses.h>
# include <termios.h>
# include <errno.h>

# define PROMPT_CONST "\033[1;31mmnii \033[1;35mshlel:"
# define PROMPT_USER " \033[1;36m\n$\033[0;0m  "

void	builtin_env(t_env_handler *env);
int		builtin_export(t_env_handler *env, t_env_str *params);
void	builtin_pwd(void);
int		builtin_unset(t_env_handler *env, char **names);
void	builtin_exit(int exit_no);
void	ms_echo(char *params[]);
void	ms_cd(char *param, t_env_handler *env);

#endif
