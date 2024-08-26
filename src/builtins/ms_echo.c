/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:33:36 by mscheman          #+#    #+#             */
/*   Updated: 2024/06/10 18:15:13 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnii_shlel.h>

static bool	is_dash_n_param(char *param);

int	builtin_echo(t_cmd *cmd)
{
	char	**args;
	bool	without_nl;
	int		i;

	args = cmd->args;
	if (!args || !args[1])
	{
		ft_putstr_fd("\n", cmd->fd_out);
		return (EXIT_SUCCESS);
	}
	i = 1;
	without_nl = false;
	while (is_dash_n_param(args[i]))
		i++;
	if (i != 1)
		without_nl = true;
	while (args[i])
	{
		ft_putstr_fd(args[i], cmd->fd_out);
		if (args[++i])
			ft_putstr_fd(" ", cmd->fd_out);
	}
	if (!without_nl)
		ft_putstr_fd("\n", cmd->fd_out);
	return (EXIT_SUCCESS);
}

static bool	is_dash_n_param(char *param)
{
	int	i;

	if (ft_strlen(param) < 2)
		return (false);
	i = 1;
	while (param[i] == 'n')
		i++;
	if (param[i])
		return (false);
	return (true);
}
