/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:29:46 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/06 18:15:00 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void command_error(t_pipex *pipex, char *str)
// {
// 	if (errno == ENOENT){
// 		ft_putstr_fd(str, 2);
// 		ft_putstr_fd(": command not found\n", 2);
// 		destroy_pipex(pipex);
// 		exit(127);
// 	}
// }

// void	ft_error(char *str)
// {
// 	perror(str);
// 	exit(127);
// }

// void	exit_error(t_pipex *pipex, char *str)
// {
// 	if (errno == ENOENT)
// 	{
// 		perror(str);
// 		destroy_pipex(pipex);
// 		exit(127);
// 	}
// 	else if (errno == EACCES)
// 	{
// 		ft_putstr_fd(str, 2);
// 		ft_putstr_fd(": permision denied\n", 2);
// 		destroy_pipex(pipex);
// 		exit(126);
// 	}
// }

void	exit_error(t_pipex *pipex, char *cmd)
{
	// close_pipe_fd(pipex);
	if (errno == ENOENT)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": comand not found\n", 2);
		destroy_pipex(pipex);
		exit(127);
	}
	else
		perror(cmd);
	destroy_pipex(pipex);
	exit(127);
}

void	ft_error(char *str, t_pipex* pipex)
{
	perror(str);
	if (pipex)
		destroy_pipex(pipex);
	exit(1);
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

void close_all_fds(void)
{
    long max_fd = sysconf(_SC_OPEN_MAX);
    if (max_fd == -1)
        max_fd = 1024;

    int fd = 0;
    while (fd < max_fd)
    {
        if (fcntl(fd, F_GETFD) != -1) 
        {
            if (close(fd) == -1)
                perror("close");
        }
        fd++;
    }
}
