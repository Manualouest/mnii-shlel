/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:29:17 by mscheman          #+#    #+#             */
/*   Updated: 2024/05/01 17:29:17 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTINS_H
#define MS_BUILTINS_H

char	*envp_find(char **envp, char *name);

void	builtin_env(t_env_handler *env);
int		builtin_export(t_env_handler *env, t_env_str *params);
void	builtin_pwd(void);
int		builtin_unset(t_env_handler *env, char **names);
void	builtin_exit(int exit_no);
void	builtin_echo(char *params[]);
void	builtin_cd(char *param, t_env_handler *env);

#endif
