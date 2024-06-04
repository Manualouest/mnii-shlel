/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:28:23 by mscheman          #+#    #+#             */
/*   Updated: 2024/05/28 15:09:41 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

int g_signal = 0;

static char *setup_prompt(void);
static char	*read_term(void);

void	free_tab(void **tab)
{
	int i;

	i = 0;
	if (!tab || !tab[i])
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	error_log(char *msg)
{
	write(STDERR_FILENO, "\033[1;31m", 7);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\033[0m", 4);
}

int	main(int argc, char *argv[], char *envp[])
{
    (void)argc, (void)argv;

	t_env_handler	*env;
	char			*input;
	t_cmd			*cmd;

	signal(SIGINT, ms_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	input = NULL;
	env = setup_env_struct(envp);
	while (1)
	{
		input = read_term();
		if (!input)
			break ;
		cmd = ms_tokeniser_main(input, envp);
		ms_exec(cmd, env, env_find(env, "PATH"));
		ms_free_cmd(cmd);
		free(input);
		g_signal = 0;
	}
	envclear(&env, free);
	rl_clear_history();
	return 0;
}

static char *read_term(void)
{
	char	*prompt;
	char	*input;

	prompt = setup_prompt();
	input = readline(prompt);
	free(prompt);
	add_history(input);
	return (input);
}

static char *setup_prompt(void)
{
	size_t	malloc_size;
	char	*work;

	malloc_size = ft_strlen(PROMPT_CONST) + ft_strlen(PROMPT_USER) + 1;
	work = malloc(sizeof(char) * malloc_size);
	ft_strlcpy(work, PROMPT_CONST""PROMPT_USER, malloc_size);
	return (work);
}
