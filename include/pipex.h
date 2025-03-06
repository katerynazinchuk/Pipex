/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:18:43 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/06 18:25:36 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <errno.h>
# include "libft.h"
# include <linux/limits.h>

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	*infile;
	char	*outfile;
	int		pipe_fd[2];
}	t_pipex;



int		ft_pipex(t_pipex *pipex, char **envp);
pid_t	child_1(t_pipex *pipex, char **envp);
pid_t	child_2(t_pipex *pipex, char **envp);
char		*find_full_path(t_pipex *pipex, char *str, char **envp);
char	**env_path(char **envp);
void	close_pipe_fd(t_pipex *pipex);
void	destroy_pipex(t_pipex *pipex);
void	ft_free(char **str);

void	exit_error(t_pipex *pipex, char *cmd);
//void	permition_error(t_pipex *pipex, char *str);
//void	command_error(t_pipex *pipex, char *str);
void	ft_error(char *str, t_pipex *pipex);
void	close_all_fds(void);



#endif