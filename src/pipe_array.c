/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:46:15 by juaho             #+#    #+#             */
/*   Updated: 2025/01/20 09:35:15 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/libft.h"
#include "../inc/pipex.h"

int	**init_pipearr(size_t pipes)
{
	int		**pipearr;
	size_t	i;

	pipearr = (int **) ft_calloc(sizeof(int *), pipes + 1);
	if (!pipearr)
		return (NULL);
	i = 0;
	while (i < pipes)
	{
		pipearr[i] = (int *) ft_calloc(sizeof(int), 2);
		if (!pipearr[i] || pipe(pipearr[i]) < 0)
		{
			destroy_pipearr(&pipearr);
			return (NULL);
		}
		i++;
	}
	return (pipearr);
}

int	destroy_pipearr(int ***pipearr)
{
	int	**ptr;
	int	i;
	int	error;

	if (!*pipearr)
		return (0);
	ptr = *pipearr;
	error = 0;
	while (*ptr)
	{
		i = 2;
		while (i--)
			if ((*ptr)[i] > 0)
				if (close((*ptr)[i]) < 0)
					error = -1;
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(*pipearr);
	*pipearr = NULL;
	return (error);
}
