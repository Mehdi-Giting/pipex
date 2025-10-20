/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:15:27 by marvin            #+#    #+#             */
/*   Updated: 2025/09/30 17:15:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **all_path)
{
	int		i;

	i = 0;
	while (all_path[i])
	{
		free(all_path[i]);
		i++;
	}
	free(all_path);
}

int	check_cmd_inside_folder(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (1);
		else
		{
			ft_printf("permission denied: %s\n", cmd);
			exit(126);
		}
	}
	ft_printf("file does not exist: %s\n", cmd);
	exit(127);
}

char	*final_path(char **all_path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*candidate;

	i = 0;
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], "/");
		candidate = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(candidate, X_OK) == 0)
		{
			free_arr(all_path);
			return (candidate);
		}
		free(candidate);
		i++;
	}
	free_arr(all_path);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*candidate;
	char	**all_path;

	i = 0;
	all_path = NULL;
	candidate = NULL;
	if (ft_strrchr(cmd, '/'))
	{
		if (check_cmd_inside_folder(cmd) == 1)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			all_path = ft_split(envp[i] + 5, ':');
		i++;
	}
	if (!all_path)
		return (NULL);
	candidate = final_path(all_path, cmd);
	return (candidate);
}
