/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:28:28 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/12 17:27:44 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		status;

	status = 0;
	pipex = NULL;
	if (argc != 5)
		ft_error("Error: Wrong number of arguments", 1);
	pipex = initialize_pipex_struct(argv);
	status = ft_pipex(pipex, envp);
	destroy_pipex(pipex);
	return (status);
}

t_pipex	*initialize_pipex_struct(char **argv)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pipex)
		ft_error("Error: Allocation failed", 1);
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->infile = argv[1];
	pipex->cmd1 = ft_split(argv[2], ' ');
	if (!pipex->cmd1 || pipex->cmd1[0] == NULL)
		error_command_split(pipex, pipex->cmd1[0]);
	pipex->cmd2 = ft_split(argv[3], ' ');
	if (!pipex->cmd2 || pipex->cmd2[0] == NULL)
		error_command_split(pipex, pipex->cmd2[0]);
	if (pipex->cmd1 == NULL || pipex->cmd2 == NULL)
	{
		destroy_pipex(pipex);
		ft_error("Allocation failed", 1);
	}
	pipex->outfile = argv[4];
	return (pipex);
}
