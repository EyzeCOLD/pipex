#include <stdio.h>
#include <stdlib.h>


void	free_arr(char ***arr);

char	**cmd_split(char *cmd);

static void	print_array(char **arr);

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		int	i = i;
		while (i < argc)
		{
			char **arr = cmd_split(argv[i]);
			if (!arr)
			{
				perror("cmd_split");
				free_arr(&arr);
				exit(1);
			}
			print_array(arr);
			free_arr(&arr);
			i++;
		}
	}
	return (0);
}

static void	print_array(char **arr)
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}
