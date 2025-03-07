/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:07:03 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/07 16:51:34 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_full_path(char **str, char **envp)
{
	int		result;
	char	**path_array;

	path_array = env_path(envp);
	if (!path_array)
		ft_error("DEBUG: PATH not found\n", 1);
	if (access(str[0], X_OK) == 0)
		return (0);
	result = combine_full_path(str, path_array);
	if(result == -1)
	{
		ft_error("Error: Malloc error", 126);
		return (ft_free(path_array), 1);
	}
	ft_free(path_array);
	return(0);
}

int combine_full_path(char **str, char **path_array)
{
	int i;
	char	path[PATH_MAX];
	char	*tmp;

	i = 0;
	while (path_array[i])
	{
		ft_strlcpy(path, path_array[i], PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, str[0], PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			tmp = ft_strdup(path);
			if (!tmp)
				return (-1);
			free(str[0]);
			str[0] = tmp;
			break ;
		}
		i++;
	}
	return(1);
}

char	**env_path(char **envp)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			str = envp[i] + 5;
			return (ft_split(str, ':'));
		}
		i++;
	}
	return (NULL);
}

void close_pipe_fd(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}
