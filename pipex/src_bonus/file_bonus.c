#include "../include/pipex_bonus.h"

// open a file named 'filename' and return the file descriptor of the file
// flag = 0: read only (infile)
// flag = 1: write only (outfile)
static int	open_file(char *filename, int flag)
{
	int	fd;

	if (flag == 0)
		fd = open(filename, O_RDONLY, 0777);
	else if (flag == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		exit_err("invalid flag", EXIT_FAILURE);
	if (fd == -1)
		error(filename);
	return (fd);
}

// open infile and set it to stdin
int	set_infile(char *infile)
{
	int	fd_infile;
	int	pipe_fd[2];

	fd_infile = open_file(infile, 0);
	if (fd_infile == -1)
	{
		if (pipe(pipe_fd) == -1)
			return (-1);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			close_pipe(pipe_fd);
			return (-1);
		}
		close_pipe(pipe_fd);
		return (-1);
	}
	if (dup2(fd_infile, STDIN_FILENO) == -1)
	{
		close(fd_infile);
		return (-1);
	}
	close(fd_infile);
	return (0);
}

// open outfile and set it to stdout
int	set_outfile(char *outfile)
{
	int	fd_outfile;

	fd_outfile = open_file(outfile, 1);
	if (fd_outfile == -1)
		return -1;
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		close(fd_outfile);
		return -1;
	}
	close(fd_outfile);
	return (0);
}