#include "../include/pipex.h"

// open a file named 'filename' and return the file descriptor of the file
// flag = 0: read only (infile)
// flag = 1: write only (outfile)
int	open_file(char *filename, int flag)
{
	int	fd;

	if (flag == 0)
		fd = open(filename, O_RDONLY, 0777);
	else if (flag == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		exit_err("invalid flag", EXIT_FAILURE);
	if (fd == -1)
		exit_err(filename, EXIT_SUCCESS);
	return (fd);
}

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
