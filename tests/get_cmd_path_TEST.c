#include <stdio.h>
#include "../pipex.h"
#include <stdlib.h>

int main(int argc, char **argv, char **envp)
{
	char ***av_arr;

	av_arr = (char ***) malloc(sizeof(char ***) * argc - 1);
	if (!av_arr)
		return (0);
	for (int i = 1; i < argc; i++)
		av_arr[i] = cmd_split(argv[i]);
	for (int i = 1; i < argc; i++)
	{
		if (expand_cmd_path(av_arr[i], envp) == -1)
		{
			perror("");
			return (1);
		}
		printf("%s\n", av_arr[i][0]);
	}
	return (0);
}
