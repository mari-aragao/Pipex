/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <maragao@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:48:52 by maragao           #+#    #+#             */
/*   Updated: 2022/08/25 17:45:14 by maragao          ###   ########.rio      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		pipex(argv, envp);
	return (0);
}

void pipex(char **argv, char **envp)
{
	int pipe_fd[2];
	int pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		error_msg("Fork error:");
	if (pid == 0)
		child_one(argv, pipe_fd, envp);
	else
	{
		close(pipe_fd[WRITE_END]);
		pid = fork();
		if (pid < 0)
			error_msg("Fork error:");
		if (pid == 0)
			child_two(argv, pipe_fd, envp);
		else
			close(pipe_fd[READ_END]);
	}
	waitpid(pid, NULL, 0);
	waitpid(pid, NULL, 0);
}

void	child_one(char **argv, int *pipe_fd, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_msg("Open error:");
	close(pipe_fd[READ_END]);
	dup2(infile, STDIN_FILENO);
	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close(infile);
	close(pipe_fd[WRITE_END]);
	exec_function(argv[2], envp);
}

void	child_two(char **argv, int *pipe_fd, char **envp)
{
	int outfile;

	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (outfile < 0)
		error_msg("Open error:");
	dup2(outfile, STDOUT_FILENO);
	dup2(pipe_fd[READ_END], STDIN_FILENO);
	close(outfile);
	close(pipe_fd[READ_END]);
	exec_function(argv[3], envp);
}
