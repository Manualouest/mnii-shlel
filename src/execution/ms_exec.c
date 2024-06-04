/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:33:15 by mscheman          #+#    #+#             */
/*   Updated: 2024/05/28 15:10:50 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

static void	exec_cmd(t_cmd *cmd, char **envp, char *path);
static void	get_path(t_cmd *cmd, char *path);
static void	correct_args(t_cmd *cmd, char *replace);

void	ms_exec(t_cmd *to_exec, t_env_handler *env)
{
	int		edge[2];
	char	**clone_env;

	clone_env = ms_format_envp(env);
	cmd_iter(to_exec, ms_exec_initfds);
	edge[0] = open("infile", O_RDONLY | O_CREAT);
	edge[1] = open("outfile", O_WRONLY);
	ms_exec_redirectupdate(to_exec, edge[0], edge[1]);
	while (to_exec)
	{
		exec_cmd(to_exec, clone_env, envp_find(clone_env, "PATH"));
		close(to_exec->fd_in);
		close(to_exec->fd_out);
		to_exec = to_exec->next;
	}
	ms_exec_closefds(to_exec);
	waitpid(-1, NULL, 0);
	free_tab((void **)clone_env);
}

static void	exec_cmd(t_cmd *cmd, char **envp, char *path)
{
	if (!cmd)
		return ;
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		get_path(cmd, path);
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		ms_exec_closefds(cmd);
		execve(cmd->args[0], cmd->args, envp);
		error_log("bowo\n");
		exit(EXIT_FAILURE);
	}
}

static void	get_path(t_cmd *cmd, char *path)
{
	char	**split_path;
	char	*work;
	int		i;

	correct_args(cmd, NULL);
	split_path = ft_split(path, ':');
	i = 0;
	while (split_path[i])
	{
		work = ft_strjoin(split_path[i], cmd->args[0]);
		if (!access(work, X_OK))
			break ;
		free(work);
		work = NULL;
		i++;
	}
	correct_args(cmd, work);
	free_tab((void **)split_path);
}

static void	correct_args(t_cmd *cmd, char *replace)
{
	char	*tmp;

	tmp = NULL;
	if (replace)
	{
		free(cmd->args[0]);
		cmd->args[0] = replace;
		return ;
	}
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
		return ;
	tmp = ft_calloc(sizeof(char), (ft_strlen(cmd->args[0]) + 2));
	tmp[0] = '/';
	ft_strlcat(tmp, cmd->args[0], ft_strlen(cmd->args[0]) + 2);
	free(cmd->args[0]);
	cmd->args[0] = tmp;
}
