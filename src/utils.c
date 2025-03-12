/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:29:46 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/12 17:27:51 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	destroy_pipex(t_pipex *pipex)
{
	ft_free(pipex->cmd1);
	ft_free(pipex->cmd2);
	free(pipex);
}

void	ft_free(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	close_pipe_fd(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}
