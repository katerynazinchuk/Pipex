/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:18:48 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/06 18:51:14 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	// int		status;

	pipex = NULL;
	if (argc != 5)
		ft_error("", NULL);
	// if(!argv[2] || argv[2] == NULL  || argv[3] == NULL)
	// 	ft_error("", NULL);
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pipex)
		ft_error("Allocation failed", pipex);
	pipex->cmd1 = ft_split(argv[2], ' ');
	if(!pipex->cmd1 || pipex->cmd1[0] == NULL)
	{
		write(2, "EXIT 1\n", 6);
		if (errno == ENOENT)
		{
			write(2, "EXIT 2\n", 6);
			ft_putstr_fd(pipex->cmd1[0], 2);
			ft_putstr_fd(": comand not found\n", 2);
			write(2, "EXIT 3\n", 6);
		}
		ft_free(pipex->cmd1);
		free(pipex);
		exit(127);
	}
	pipex->cmd2 = ft_split(argv[3], ' ');
	if(!pipex->cmd2 || pipex->cmd2[0] == NULL)
	{
		ft_free(pipex->cmd2);
		free(pipex);
		write(2, "EXIT EXIT\n", 9);
		exit(1);
	}
	if (pipex->cmd1 == NULL || pipex->cmd2 == NULL)
		ft_error("", pipex);
	pipex->infile = argv[1];
	pipex->outfile = argv[4];
	ft_pipex(pipex, envp);
	destroy_pipex(pipex);
	close_all_fds();
	return (1);
}

int	ft_pipex(t_pipex *pipex, char **envp)
{
	pid_t	pid[2];
	int		status;

	if (pipe(pipex->pipe_fd) < 0)
		ft_error("Error: Pipe error", pipex);
	pid[0] = child_1(pipex, envp);
	if (pid[0] < 0)
		ft_error("Error: Fork error", pipex);
	pid[1] = child_2(pipex, envp);
	if (pid[1] < 0)
	{
		waitpid(pid[0], NULL, 0);// check all arguments meaning 
		ft_error("Error: Fork error", pipex);
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
		ft_error("Error: Fork error", pipex);
	if (pid == 0)
	{
		infile_fd = open(pipex->infile, O_RDONLY);
		if (infile_fd < 0)
			exit_error(pipex, pipex->infile);
		if (!find_full_path(pipex, pipex->cmd1[0], envp))
			exit_error(pipex, pipex->cmd1[0]);
		close(pipex->pipe_fd[0]);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		dup2(infile_fd, STDIN_FILENO);
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
		ft_error("Error: Fork error", pipex);
	if (pid == 0)
	{
		outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd < 0)
			exit_error(pipex, pipex->outfile);
		
		if (!find_full_path(pipex, pipex->cmd2[0], envp))
			exit_error(pipex, pipex->cmd2[0]);
		close(pipex->pipe_fd[1]);
		dup2(pipex->pipe_fd[0], STDIN_FILENO);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		close(pipex->pipe_fd[0]);
		execve(pipex->cmd2[0], pipex->cmd2, envp);
		exit_error(pipex, pipex->cmd2[0]);
	}
	return (pid);
	}
	