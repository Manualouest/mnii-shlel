/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscheman <mscheman@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:28:23 by mscheman          #+#    #+#             */
/*   Updated: 2024/04/23 18:20:33 by mscheman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *setup_prompt(char *dir);
static char	*read_term(void);

int	main(int argc, char **argv, char **envp)
{
	char *input;
	(void)argc, (void)argv;

	setup_env_struct(envp);
	return (0);


	input = (char *)1;
	while (input != NULL)
	{
		input = read_term();
		printf("\033[0;0minput is: %s\n", input);
		free(input);
	}
	rl_clear_history();
}

static char *read_term(void)
{
	char	*prompt;
	char	*path;
	char	*user;

	path = getcwd(NULL, 64);
	prompt = setup_prompt(path);
	free(path);
	user = readline(prompt);
	free(prompt);
	add_history(user);
	return (user);
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