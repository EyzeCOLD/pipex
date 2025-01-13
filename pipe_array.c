/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:27:07 by juaho             #+#    #+#             */
/*   Updated: 2025/01/12 11:48:33 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

static void	free_pipe_arr(int ***arr);
static int	**alloc_pipe_arr(size_t	n);
static void	close_and_free_pipe_arr(int ***arr);

int	**pipe_array(size_t n)
{
	int		**ret;
	size_t	i;

	ret = alloc_pipe_arr(n);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (pipe(ret[i]) == -1)
		{
			perror("pipe");
			close_and_free_pipe_arr(&ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}

static void	free_pipe_arr(int ***arr)
{
	size_t	i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

static int	**alloc_pipe_arr(size_t	n)
{
	int		**ret;
	size_t	i;

	ret = (int **) malloc(sizeof(int *) * n);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ret[i] = (int *) ft_calloc(sizeof(int), 2);
		if (!ret[i])
		{
			free_pipe_arr(&ret);
			return (NULL);
		}
		ft_memset(ret[i], -1, 2);
		i++;
	}
	return (ret);
}

static void	close_and_free_pipe_arr(int ***arr)
{
