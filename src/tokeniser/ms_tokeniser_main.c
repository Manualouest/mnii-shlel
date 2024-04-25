/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokeniser_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:06:19 by mbirou            #+#    #+#             */
/*   Updated: 2024/04/25 20:04:33 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokeniser.h>

int	ms_check_for_pipes(char *line)
{
	int	i;
	int	nb_pipes;

	i = -1;
	nb_pipes = 0;
	while (line[++i])
		if (line[i] == '|')
			nb_pipes ++;
	return (nb_pipes);
}

void	ms_init_pipes(t_pipes *main, int nb_pipes)
{
	t_pipes *temp_pipe;
	t_pipes	*start;
	int		is_first;

	is_first = 1;
	main->right = NULL;
	if (nb_pipes != 0)	
	{
		while (nb_pipes > 0)
		{
			if (is_first == 1)
				temp_pipe = malloc(sizeof(*temp_pipe));
			temp_pipe->command = malloc(sizeof(*temp_pipe->command));
			if (nb_pipes > 1)
				temp_pipe->right = malloc(sizeof(*temp_pipe));
			else
				temp_pipe->right = NULL;
			if (is_first == 1)
			{
				is_first = 0;
				start = temp_pipe;
			}
			temp_pipe = temp_pipe->right;
			nb_pipes --;
		}
		main->right = start;
	}
}

void	ms_fill_pipes_main(t_pipes *pipes, char *line)
{
	int	i;

	i = 0;
	while (pipes != NULL)
	{
		ms_init_cmd(pipes->command, line, &i);
		ms_fill_params(pipes->command, pipes->command->params, line, &i);
		if (ms_am_i_at_the_next_pipe(line, i) == 0)
			ms_head_to_next_pipe(line, &i);
		pipes = pipes->right;
	}
}

t_pipes	*ms_tokeniser_main(char *line)
{
	t_pipes	*main;
	int		nb_pipes;

	main = malloc(sizeof(*main));
	main->command = malloc(sizeof(*main->command));
	main->right = NULL;
	nb_pipes = ms_check_for_pipes(line);
	ms_init_pipes(main, nb_pipes);
	ms_fill_pipes_main(main, line);
	return (main);
}
