/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:39:47 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/26 23:24:57 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

char	*find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp_env("PATH=", env[i]) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*join_paths(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			break ;
		path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (!path)
			break ;
		if (access(path, F_OK | X_OK) == 0)
		{
			free_all(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_all(paths);
	return (NULL);
}

char	*check_path(char *cmd, char **env)
{
	char	*path;
	char	**paths;

	path = find_path(env);
	if (!path)
		return (NULL);
	paths = ft_split(path + 5, ':');
	if (!paths)
	{
		free_all(paths);
		paths = NULL;
		return (NULL);
	}
	return (join_paths(paths, cmd));
}

bool	find_count_exe(char **argv, int argc, t_pip *struc)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	struc->here_doc = -1;
	struc->exec_pos = 0;
	while (argv[i])
	{
		if (!ft_strcmp_trimmed("here_doc", argv[i]))
		{
			res += 1;
			struc->here_doc = i;
		}
		if (!ft_strcmp_trimmed("./pipex", argv[i]))
		{
			struc->exec_pos = i;
			res = i;
		}
		i++;
	}
	if ((argc - res) < 5)
		return (0);
	return (1);
}
