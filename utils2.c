/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <maragao@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:09:03 by maragao           #+#    #+#             */
/*   Updated: 2022/08/30 17:47:32 by maragao          ###   ########.rio      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_free(char **mat)
{
	int	i;

	i = 0;
	while (mat[i++])
		free(mat[i]);
	free(mat);
}

char	*strdup_mod(char *s, int n)
{
	int		i;
	char	*ptr;

	ptr = (char *)malloc((n + 1) * sizeof(char));
	if (!ptr)
		error_msg("Allocation Error:");
	i = 0;
	while (i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

int	mat_len(char *s, char c)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (s[i++] != 0)
		if (s[i] == c)
			len++;
	return (len + 1);
}

char	**ft_split(char *s, char c)
{
	char	**mat;
	int		mat_size;
	int		i;
	int		mat_count;

	mat_size = mat_len(s, c);
	mat = (char **) malloc((mat_size + 1) * sizeof(char *));
	if (!mat)
		error_msg("Allocation Error:");
	mat_count = 0;
	while (mat_count < mat_size)
	{
		i = 0;
		while (s[i] != c && s[i] != 0)
			i++;
		mat[mat_count] = strdup_mod(s, i);
		if (!mat[mat_count++])
			error_alloc(mat, mat_count);
		s += i + 1;
	}
	mat[mat_count] = NULL;
	return (mat);
}
