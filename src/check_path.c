/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:07:03 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/03/06 18:25:34 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_full_path(t_pipex *pipex, char *str, char **envp)
{
	int i;
	char **path_array;
	char full_path[PATH_MAX];
	
	path_array = env_path(envp);
	if (!path_array)
		ft_error("Error: Path not found", pipex);
	if(access(str, X_OK) == 0)
		return (str);
	else
	{
		i = 0;
		while(path_array[i])
		{
			ft_strlcpy(full_path, path_array[i], PATH_MAX);
			ft_strlcat(full_path, "/", PATH_MAX);
			ft_strlcat(full_path, str, PATH_MAX);
			if (access(full_path, X_OK) == 0)
			{
				str = ft_strdup(full_path);
				if (!str)
				{
					ft_free(path_array);
					ft_error("Error: Malloc error", pipex);
				}
				ft_free(path_array);
				return (str);
			}
			i++;
		}
	}
	ft_free(path_array);
	return (NULL);
}
// int	full_path(char **cmd, char **envp)
// {
// 	int		i;
// 	char	**path_array;
// 	char	*tmp;
// 	char	path[PATH_MAX];

// 	path_array = env_path(envp);
// 	if (!path_array)
// 		ft_error("DEBUG: PATH not found\n");
// 	if (access(cmd[0], X_OK) == 0)
// 		return (0);
// 	i = 0;
// 	while (path_array[i])
// 	{
// 		ft_strlcpy(path, path_array[i], PATH_MAX);
// 		ft_strlcat(path, "/", PATH_MAX);
// 		ft_strlcat(path, cmd[0], PATH_MAX);
// 		if (access(path, X_OK) == 0)
// 		{
// 			tmp = ft_strdup(path);
// 			if (!tmp)
// 			{
// 				ft_error("Error: Malloc error");
// 				return (ft_free(path_array), 1);
// 			}
// 			free(cmd[0]);
// 			cmd[0] = tmp;
// 			break ;
// 		}
// 		i++;
// 	}
// 	ft_free(path_array);
// 	return(0);
// }

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
