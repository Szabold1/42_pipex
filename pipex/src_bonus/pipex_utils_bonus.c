#include "../include/pipex_bonus.h"

// close the pipe
void	close_pipe(int fd_pipe[2])
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
}

// loop through 'arr' and free each string, then free 'arr'
void	free_arr_of_strs(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
