/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <maragao@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:49:00 by maragao           #+#    #+#             */
/*   Updated: 2022/08/30 17:46:42 by maragao          ###   ########.rio      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	complete_path(char **paths)
{
	int		i;
	char	*aux;

	i = 0;
	while (paths[i] != 0)
	{
		aux = strdup_mod(paths[i], ft_strlen(paths[i]));
		free (paths[i]);
		paths[i] = ft_strjoin(aux, "/");
		if (!paths[i])
			error_alloc(paths, i);
		free(aux);
		i++;
	}	
}

char	**get_paths(char **paths, char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
				error_msg("Allocation error");
			complete_path(paths);
			return (paths);
		}
		i++;
	}
	error_msg("Execution error");
	return (NULL);
}

void	run_paths(char **paths, char **args, char *cmd_name, char **envp)
{
	char	*temp_path;
	int		i;

	i = 0;
	while (paths[i] != 0)
	{
		temp_path = (ft_strjoin(paths[i], cmd_name));
		if (!temp_path)
			error_msg("Allocation error");
		if (access(temp_path, F_OK | X_OK) == 0)
		{
			get_free(paths);
			execve(temp_path, args, envp);
		}
		free(temp_path);
		i++;
	}
	get_free(paths);
	get_free(args);
	error_msg("Execution error");
}

void	exec_function(char *cmd, char **envp)
{
	char	**args;
	char	**paths;
	char	*cmd_name;

	args = ft_split(cmd, ' ');
	if (!args)
		error_msg("Allocation Error");
	cmd_name = args[0];
	paths = NULL;
	paths = get_paths(paths, envp);
	run_paths(paths, args, cmd_name, envp);
}
