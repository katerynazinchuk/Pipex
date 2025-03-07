/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:29:46 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/07 18:54:20 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_command_split(t_pipex *pipex, char *str)
{
	ft_putstr_fd("'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': comand not found\n", 2);
	if(pipex->cmd1)
		ft_free(pipex->cmd1);
	if(pipex->cmd2)
		ft_free(pipex->cmd2);
	free(pipex);
	exit(127);
}

void	exit_error(t_pipex *pipex, char *str)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": comand not found\n", 2);
		destroy_pipex(pipex);
		exit(127);
	}
	else
		perror(str);
	destroy_pipex(pipex);
	exit(127);
}

void	ft_error(char *str, int error_number)
{
	perror(str);
	exit(error_number);
}

void	destroy_pipex(t_pipex *pipex)
{
	ft_free(pipex->cmd1);
	ft_free(pipex->cmd2);
	free(pipex);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}


