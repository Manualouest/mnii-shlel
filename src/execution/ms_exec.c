/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:33:15 by mscheman          #+#    #+#             */
/*   Updated: 2024/09/02 11:09:57 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

static int	exec_pipe_builtin(t_cmd *to_exec, char ***env);

void	ms_exec(t_cmd *to_exec, char ***env, bool is_pipe)
{
	int		status;

	signal(SIGINT, SIG_IGN);
	if (is_pipe)
	{
		ms_exec_pipe(to_exec, env);
		signal(SIGINT, ms_sig_handler);
		return ;
	}
	if (ms_exec_builtin(to_exec, env) != -1)
	{
		signal(SIGINT, ms_sig_handler);
		return ;
	}
	child_exec(to_exec, env);
	waitpid(to_exec->pid, &status, 0);
	if (WIFEXITED(status))
		g_signal = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal = WTERMSIG(status) + 128;
	if (g_signal == 130)
		write(1, "\n", 1);
	else if (g_signal == 131)
		ft_putstr_fd("Quit\n", 2);
	signal(SIGINT, ms_sig_handler);
}

void	child_exec(t_cmd *to_exec, char ***env)
{
	if (!to_exec)
		return ;
	to_exec->pid = fork();
	if (to_exec->pid < -1)
		error_log("fork failed", '\n');
	if (to_exec->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (exec_pipe_builtin(to_exec, env) != -1)
			exit(g_signal);
		if (to_exec->fd_in != -1 && dup2(to_exec->fd_in, STDIN_FILENO) == -1)
			ms_dup2_quit(to_exec, *env);
		if (to_exec->fd_out != -1 && dup2(to_exec->fd_out, STDOUT_FILENO) == -1)
			ms_dup2_quit(to_exec, *env);
		ms_exec_closefds(to_exec->first);
		rl_clear_history();
		ms_child_getpath(to_exec, envp_find(*env, "PATH"));
		execve(to_exec->args[0], to_exec->args, *env);
		ms_execve_quit(to_exec, *env);
	}
}

static int	exec_pipe_builtin(t_cmd *to_exec, char ***env)
{
	int	ret;

	ret = ms_exec_builtin(to_exec, env);
	if (ret != -1)
	{
		g_signal = ret;
		ms_exec_closefds(to_exec->first);
		ms_exec_unleak(to_exec, (*env));
	}
	return (ret);
}
