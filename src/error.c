/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:06:11 by juaho             #+#    #+#             */
/*   Updated: 2025/01/20 12:30:48 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/libft.h"

void	err_comm_not_found(char *cmd)
{
	char *emsg;

	emsg = ft_strjoin(cmd, ": command not found\n");
	if (!emsg)
		return ;
	ft_putstr_fd(emsg, 2);
	free(emsg);
}
