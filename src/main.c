/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:04:53 by juaho             #+#    #+#             */
/*   Updated: 2025/01/19 21:37:04 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_pipex px;

	if (init_pipex(&px, argc, argv, envp) < 1)
		perror("pipex");

	printf("px.env_path:\n");
	for (int i = 0; px.env_path[i]; i++)
		printf("\t%s\n", px.env_path[i]);

	printf("\npx.pwd:\n");
	printf("\t%s\n", px.pwd);

	printf("\npx.infile_path:\n");
	printf("\t%s\n", px.infile_path);

	printf("\npx.infile_fd:\n");
	printf("\t%d\n", px.infile_fd);

	printf("\npx.outfile_path:\n");
	printf("\t%s\n", px.outfile_path);

	printf("\npx.outfile_fd:\n");
	printf("\t%d\n", px.outfile_fd);

	printf("\npx.pipe_arr:\n");
	for (int i = 0; px.pipe_arr[i]; i++)
		printf("\tPipe [%d]: R[%d] W[%d]\n", i, px.pipe_arr[i][0], px.pipe_arr[i][1]);

	printf("\npx.av_arr:\n");
	for (int i = 0; px.av_arr[i]; i++)
	{
		printf("\tav [%d]: ", i);
		for (int j = 0; px.av_arr[i][j]; j++)
		{
			printf("%s", px.av_arr[i][j]);
			if (px.av_arr[i][j + 1])
				printf(", ");
		}
	}
	return (destroy_pipex(&px));
}
