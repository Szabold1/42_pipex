#include "../include/pipex.h"

// open 'filename' and return its file descriptor, or -1 if error occurs
// flag = 0: read only (infile)
// flag = 1: write, create, truncate (outfile)
static int	open_file(char *filename, int flag)
{
	int	fd;

	if (flag == 0)
		fd = open(filename, O_RDONLY, 0777);
	else if (flag == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = -1;
	return (fd);
}

// open the infile and handle errors
// return 0 if successful, otherwise return -1
int	set_infile(t_data *data)
{
	data->in_fd = open_file(data->infile, 0);
	if (data->in_fd == -1)
	{
		data->in_fd = open_file("/dev/null", 0);
		if (data->in_fd == -1)
			return (err_msg("/dev/null failed"), -1);
		data->skip_first_cmd = true;
		err_msg(data->infile);
	}
	return (0);
}

// open outfile in write, create, truncate mode
// return 0 if successful, otherwise return -1
int	set_outfile(t_data *data)
{
	data->out_fd = open_file(data->outfile, 1);
	if (data->out_fd == -1)
		return (err_msg(data->outfile), -1);
	return (0);
}
