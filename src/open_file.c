/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:18:15 by juaho             #+#    #+#             */
/*   Updated: 2025/01/28 11:17:48 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../inc/pipex.h"

void	open_file(char *file, t_pipex *px, int flags)
{
	px->fd = open(file, flags, 00644);
	if (px->fd < 0)
	{
		err_with_filename(file);
		close_pipex(px, 1);
	}
}
