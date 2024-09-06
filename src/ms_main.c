/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:28:23 by mscheman          #+#    #+#             */
/*   Updated: 2024/09/06 11:05:38 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

void		ms_cmd_test_printer(t_cmd *full_line);
static void	shell_loop(char ***ms_env);
static char	*setup_prompt(char *dir);
static char	*read_term(void);

int	g_signal = 0;

void	error_log(char *msg, char last_char)
{
	write(STDERR_FILENO, "\033[1;31m", 7);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, &last_char, 1);
	write(STDERR_FILENO, "\033[0m", 4);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			**ms_env;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	signal(SIGINT, ms_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	ms_env = tab_clone(envp);
	shell_loop(&ms_env);
	free_tab((void **)ms_env);
	rl_clear_history();
	exit(g_signal);
}

static void	shell_loop(char ***ms_env)
{
	char	*input;
	t_cmd	*cmd;

	input = NULL;
	while (true)
	{
		cmd = NULL;
		input = read_term();
		if (!input)
			break ;
		if (input[0])
			cmd = ms_tokeniser_main(input, *ms_env);
		if (cmd)
		{
			if (g_signal == 0 && ((!cmd->args[0] || !cmd->args[0][0])))
				g_signal = 127;
			else if (cmd->error_id < 2 && g_signal == 0)
				ms_exec(cmd, ms_env, cmd->next != NULL);
			if (cmd)
				ms_free_cmd(cmd);
		}
		else if (g_signal == 0 && input[0])
			ms_handle_errors(NULL, -1, MS_FAIL_STRUCT, NULL);
		free(input);
	}
}

static char	*read_term(void)
{
	char	*prompt;
	char	*path;
	char	*input;

	path = getcwd(NULL, 0);
	prompt = setup_prompt(path);
	free(path);
	input = readline(prompt);
	free(prompt);
	if (input && input[0])
		add_history(input);
	return (input);
}

static char	*setup_prompt(char *dir)
{
	size_t	malloc_size;
	bool	dir_exists;
	char	*work;

	dir_exists = true;
	if (dir == NULL)
	{
		dir = ft_strdup("i forgorrrr");
		dir_exists = false;
	}
	malloc_size = ft_strlen(PROMPT_CONST) + ft_strlen(PROMPT_USER);
	malloc_size += ft_strlen(dir) + ft_strlen("\001\033[1;32m\002") + 1;
	work = malloc(sizeof(char) * malloc_size);
	ft_strlcpy(work, PROMPT_CONST, ft_strlen(PROMPT_CONST) + 1);
	ft_strlcat(work, " \001\033[1;32m\002", malloc_size);
	ft_strlcat(work, dir, malloc_size);
	ft_strlcat(work, PROMPT_USER, malloc_size);
	if (!dir_exists)
		free(dir);
	return (work);
}
