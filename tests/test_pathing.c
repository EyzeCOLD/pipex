#include <stdio.h>
#include <stdlib.h>
#include "pipex.h"
#include "libft/libft.h"

int main(int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		char	*path;
		char	**av;

		if (!env_path)
		{
			printf("PATH variable not found\n");
			return (1);
		}
		int	i = 1;
		while (i < argc)
		{
			av = cmd_split(argv[i]); 
			if (!av)
			{
				free(env_path);
				return (1);
			}
			path = get_cmd_path_for_execve(av, env_path);
			if (!path)
			{
				printf("cmd not found\n");
				free_arr(&av);
				return (1);
			}
			free(av[0]);
			av[0] = path;
			if (fork_exec(av, envp) == -1)
			{
				free_arr(&av);
				break ;
			}
			free_arr(&av);
			i++;
		}
		free_arr(&env_path);
	}
	return (0);
}
