/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <maragao@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:48:52 by maragao           #+#    #+#             */
/*   Updated: 2022/08/27 15:30:49 by maragao          ###   ########.rio      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		pipex(argv, envp);
	else
		write(1, "Everything out of order", 23);
	return (0);
}

void	pipex(char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(pipe_fd);
	pid1 = fork();
	if (pid1 < 0)
		error_msg("Fork error:");
	if (pid1 == 0)
		child_one(argv, pipe_fd, envp);
	if (pid1 > 0)
	{
		close(pipe_fd[WRITE_END]);
		pid2 = fork();
		if (pid2 < 0)
			error_msg("Fork error:");
		if (pid2 == 0)
			child_two(argv, pipe_fd, envp);
		if (pid2 > 0)
			close(pipe_fd[READ_END]);
		waitpid(pid2, NULL, 0);
	}
	waitpid(pid1, NULL, 0);
}

void	child_one(char **argv, int *pipe_fd, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_msg("Open error:");
	close(pipe_fd[READ_END]);
	dup2(infile, 0);
	close(infile);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	exec_function(argv[2], envp);
}

void	child_two(char **argv, int *pipe_fd, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (outfile < 0)
		error_msg("Open error:");
	dup2(outfile, STDOUT_FILENO);
	dup2(pipe_fd[READ_END], STDIN_FILENO);
	close(outfile);
	close(pipe_fd[READ_END]);
	exec_function(argv[3], envp);
}
