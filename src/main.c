/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:04:53 by juaho             #+#    #+#             */
/*   Updated: 2025/01/20 15:16:55 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/pipex.h"

//static void	print_pipex(t_pipex px);

int main(int argc, char **argv, char **envp)
{
	t_pipex px;
	int		error;

	error = init_pipex(&px, argc, argv, envp);
	if (error < 0)
	{
		if (error == -1)
			perror("pipex");
		if (destroy_pipex(&px) < 0)
			perror("pipex");
		return (1);
	}
	if (exec_commands(argc - 3, &px, envp) < 0)
	{
		perror("pipex");
		if (destroy_pipex(&px) < 0)
			perror("pipex");
		return (1);
	}
	return (destroy_pipex(&px));
}

//static void	print_pipex(t_pipex px)
//{
//	printf("px.env_path:\n");
//	for (int i = 0; px.env_path[i]; i++)
//		printf("\t%s\n", px.env_path[i]);
//
//	printf("\npx.pwd:\n");
//	printf("\t%s\n", px.pwd);
//
//	printf("\npx.infile_path:\n");
//	printf("\t%s\n", px.infile_path);
//
//	printf("\npx.infile_fd:\n");
//	printf("\t%d\n", px.infile_fd);
//
//	printf("\npx.outfile_path:\n");
//	printf("\t%s\n", px.outfile_path);
//
//	printf("\npx.outfile_fd:\n");
//	printf("\t%d\n", px.outfile_fd);
//
//	printf("\npx.pipe_arr:\n");
//	for (int i = 0; px.pipe_arr[i]; i++)
//		printf("\tPipe [%d]: R[%d] W[%d]\n", i, px.pipe_arr[i][0], px.pipe_arr[i][1]);
//
//	printf("\npx.av_arr:\n");
//	for (int i = 0; px.av_arr[i]; i++)
//	{
//		printf("\tav [%d]: ", i);
//		for (int j = 0; px.av_arr[i][j]; j++)
//		{
//			printf("%s", px.av_arr[i][j]);
//			if (px.av_arr[i][j + 1])
//				printf(", ");
//		}
//		printf("\n");
//	}
//}
