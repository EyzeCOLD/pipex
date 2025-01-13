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
#include "pipex.h"

static void	free_pipe_arr(int ***arr, size_t size);
static int	**alloc_pipe_arr(size_t	size);

int	**pipe_array(size_t size)
{
	int		**ret;
	size_t	i;

	ret = alloc_pipe_arr(size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (pipe(ret[i]) == -1)
		{
			perror("pipe");
			close_and_free_pipe_arr(&ret, size);
			return (NULL);
		}
		i++;
	}
	return (ret);
}

static void	free_pipe_arr(int ***arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && (*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

static int	**alloc_pipe_arr(size_t	size)
{
	int		**ret;
	size_t	i;

	ret = (int **) ft_calloc(sizeof(int *), size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = (int *) ft_calloc(sizeof(int), 2);
		if (!ret[i])
		{
			free_pipe_arr(&ret, size);
			return (NULL);
		}
		ret[i][0] = -1;
		ret[i][1] = -1;
		i++;
	}
	return (ret);
}

void	close_and_free_pipe_arr(int ***arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && (*arr)[i])
	{
		if ((*arr)[i][0] != -1)
			close((*arr)[i][0]);
		if ((*arr)[i][1] != -1)
			close((*arr)[i][1]);
		i++;
	}
	free_pipe_arr(arr, size);
}
