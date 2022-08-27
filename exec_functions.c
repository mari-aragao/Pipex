/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <maragao@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:49:00 by maragao           #+#    #+#             */
/*   Updated: 2022/08/27 15:14:19 by maragao          ###   ########.rio      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
char    **get_paths(char **paths, char **envp)
{
    int     i;

    i = 0;
    while (envp[i] != 0)
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            paths = ft_split(envp[i] + 5, ':');
            if (!paths)
				error_msg("Allocaton error:");
            i = 0;
            while (paths[i] != 0)
            {
                paths[i] = ft_strjoin(paths[i], "/");
                if (!paths[i])
                    error_alloc(paths, i);
                i++;
            }
            return (paths);
        }
        i++;
    }
	error_msg("Execution error:");
	return(NULL);
}

void   exec_function(char *cmd, char **envp)
{
    char    **args;
    char    **paths;
    char    *cmd_name;
    char    *temp_path;
    int     i;


    args = ft_split(cmd, ' ');
	if (!args)
        error_msg("Allocation Error: ");
    cmd_name = args[0];
	paths = NULL;
	paths = get_paths(paths, envp);
	//if(!paths)
		//error;
    i = 0;
    while (paths[i] != 0)
    {
        temp_path = (ft_strjoin (paths[i], cmd_name));
        if (!temp_path)
			error_msg("Allocation error");
        if (access(temp_path, X_OK) == 0)
		{
			//free paths
			execve(temp_path, args, envp);
		}
        free(temp_path);
        i++;
    }
    error_msg("Execution error:");
}
/*
int main(int argc, char **argv, char **envpp)
{
	char *cmd = argv[1];
	(void) argc;
	exec_function(cmd, envp);
	return 0;
}*/
