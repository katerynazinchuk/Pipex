/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:01:46 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/12 17:27:37 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_file_open(t_pipex *pipex, char *str)
{
	close_pipe_fd(pipex);
	perror(str);
	destroy_pipex(pipex);
	exit(1);
}

void	error_command_split(t_pipex *pipex, char *str)
{
	ft_putstr_fd("'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': Comand not found\n", 2);
	destroy_pipex(pipex);
	exit(127);
}

void	exit_error(t_pipex *pipex, char *str)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Comand not found\n", 2);
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
