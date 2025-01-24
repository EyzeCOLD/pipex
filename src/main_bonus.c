/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:43:41 by juaho             #+#    #+#             */
/*   Updated: 2025/01/23 14:54:30 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex px;

	if (argc < 5)
		return (-1);
	if (init_pipex(&px, envp) < 0)
	{
		perror("pipex");
		close_pipex(&px);
	}
	if (ft_strncmp(argv[1], "heredoc", ft_strlen(argv[1])))
	{
		//HEREDOC MODE ENGAGE
	}
	exec_commands(argc, argv, &px);
	return (0);
}
