/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:18:48 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/12 17:27:47 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipex(t_pipex *pipex, char **envp)
{
	pid_t	pid[2];
	int		status;

	if (pipe(pipex->pipe_fd) < 0)
		ft_error("Error: Pipe error", 1);
	pid[0] = child_1(pipex, envp);
	if (pid[0] < 0)
	{
		close_pipe_fd(pipex);
		ft_putstr_fd("Error: Fork error", 2);
	}
	pid[1] = child_2(pipex, envp);
	if (pid[1] < 0)
	{
		close_pipe_fd(pipex);
		ft_putstr_fd("Error: Fork error", 1);
	}
	close_pipe_fd(pipex);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

pid_t	child_1(t_pipex *pipex, char **envp)
{
	pid_t	pid;
	int		infile_fd;

	pid = fork();
	if (pid < 0)
		return (ft_error("Error: Fork error", 1), pid);
	if (pid == 0)
	{
		infile_fd = open(pipex->infile, O_RDONLY);
		if (infile_fd < 0)
			error_file_open(pipex, pipex->infile);
		if (find_full_path(pipex->cmd1, envp))
			exit_error(pipex, pipex->cmd1[0]);
		close(pipex->pipe_fd[0]);
		if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
			ft_error("Dup2 error", 1);
		if (dup2(infile_fd, STDIN_FILENO) == -1)
			ft_error("Dup2 error", 1);
		close(infile_fd);
		close(pipex->pipe_fd[1]);
		execve(pipex->cmd1[0], pipex->cmd1, envp);
		exit_error(pipex, pipex->cmd1[0]);
	}
	return (pid);
}

pid_t	child_2(t_pipex *pipex, char **envp)
{
	pid_t	pid;
	int		outfile_fd;

	pid = fork();
	if (pid < 0)
		ft_error("Error: Fork error", 1);
	if (pid == 0)
	{
		outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd < 0)
			error_file_open(pipex, pipex->outfile);
		if (find_full_path(pipex->cmd2, envp))
			exit_error(pipex, pipex->cmd2[0]);
		close(pipex->pipe_fd[1]);
		if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
			ft_error("Dup2 error", 1);
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
			ft_error("Dup2 error", 1);
		close(outfile_fd);
		close(pipex->pipe_fd[0]);
		execve(pipex->cmd2[0], pipex->cmd2, envp);
		exit_error(pipex, pipex->cmd2[0]);
	}
	return (pid);
}
