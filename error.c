/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <maragao@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:31:45 by maragao           #+#    #+#             */
/*   Updated: 2022/08/25 18:17:37 by maragao          ###   ########.rio      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_alloc(char **mat, int i)
{
	if (!mat)
		error_msg("Allocation Error:");
	while (--i >= 0)
			free(mat[i]);
		free(mat);
	error_msg("Allocation Error:");
}

void	error_msg(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
