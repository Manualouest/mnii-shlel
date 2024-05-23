/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:28:23 by mscheman          #+#    #+#             */
/*   Updated: 2024/04/26 14:16:01 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *setup_prompt(char *dir);
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

//static t_cmd *lololol(char **pipes)
//{
//	char **cmd;
//	t_cmd *joseph = NULL;
//	t_cmd *joestar = NULL;
//	int i = 0;
//
//	while (pipes[i]){
//		cmd = ft_split(pipes[i], ' ');
//		joseph = cmd_new(cmd);
//		cmd_add_back(&joestar, joseph);
//		i++;
//	}
//	return (joestar);
//}

int	main(int argc, char *argv[], char *envp[])
{
    (void)argc, (void)argv;

	t_env_handler	*env;
	char	**content = NULL;
	char	**heredoc;
	char	*input = NULL;
//	t_cmd	*cmd;

	env = setup_env_struct(envp);
	while (1)
	{
		input = read_term();
		if (!input)
			break ;
//		content = ft_split(input, '|');
//		cmd = lololol(content);
//
//		free(input);
//		free_tab((void **)content);
//		ms_exec(cmd, envp, env_find(env, "PATH"));
//		cmd_clear(&cmd, free_tab);
	}
	envclear(&env, free);
	rl_clear_history();
	for (int i = 0; content[i]; ++i) {
		printf("%d = %s\n", i, content[i]);
	}
	free_tab((void **)content);
	return 0;
}

static char *read_term(void)
{
	char	*prompt;
	char	*path;
	char	*input;

	path = getcwd(NULL, 64);
	prompt = setup_prompt(path);
	free(path);
	input = readline(prompt);
	free(prompt);
	add_history(input);
	return (input);
}

static char *setup_prompt(char *dir)
{
	size_t	malloc_size;
	char	*work;

	if (dir == NULL)
		dir = ft_strdup("whree tf are u???");
	malloc_size = ft_strlen(PROMPT_CONST) + ft_strlen(PROMPT_USER);
	malloc_size += ft_strlen(dir) + ft_strlen("\033[1;32m") + 1;
	work = malloc(sizeof(char) * malloc_size);
	ft_strlcpy(work, PROMPT_CONST, ft_strlen(PROMPT_CONST) + 1);
	ft_strlcat(work, " \033[1;32m", malloc_size);
	ft_strlcat(work, dir, malloc_size);
	ft_strlcat(work, PROMPT_USER, malloc_size);
	return (work);
}