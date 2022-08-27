/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <maragao@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:50:34 by maragao           #+#    #+#             */
/*   Updated: 2022/08/27 15:13:54 by maragao          ###   ########.rio      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

# define READ_END	0
# define WRITE_END	1

int		main(int argc, char **argv, char **envp);
void	pipex(char **argv, char **envp);
void	child_one(char **argv, int *pipe_fd, char **envp);
void	child_two(char **argv, int *pipe_fd, char **envp);
void	error_alloc(char **mat, int i);
char 	*strdup_mod(char *s, int n);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	**get_paths(char **paths, char **envp);
void    exec_function(char *cmd, char **envp);
void	error_msg(const char *str);

#endif
