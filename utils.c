/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <maragao@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:48:37 by maragao           #+#    #+#             */
/*   Updated: 2022/08/25 17:48:28 by maragao          ###   ########.rio      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char 	*strdup_mod(char *s, int n)
{
	int 	i;
	char 	*ptr;

	ptr = (char *)malloc((n + 1) * sizeof(char));
	if (!ptr)
		error_alloc(NULL, 0);
	i = 0;
	while (i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	**ft_split(char *s, char c)
{
	char **mat;
	int mat_size;
	int i;
	int mat_count;

	i = 0;
	mat_size = 1;
	while (s[i++] != 0)
		if (s[i] == c)
			mat_size++;
	mat = (char **) malloc((mat_size + 1) * sizeof(char *));
	if (!mat)
		error_alloc(NULL, 0);
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

int		ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && i < n - 1)
		i++;
	return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
}

size_t	ft_strlen(char *s)
{
	size_t len;

	len = 0;
	while (s[len] != 0)
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	
	ptr = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		error_alloc (NULL, 0);
	i = 0;
	while (*s1 != 0)
	{
		ptr[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 != 0)
	{
		ptr[i] = *s2;
		i++;
		s2++;
	}
	ptr[i] = 0;
	free (s1);
	return (ptr);
}
