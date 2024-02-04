#include "../include/pipex_bonus.h"

// open 'filename' and return its file descriptor, or -1 if error occurs
// flag = 0: read only (infile)
// flag = 1: write, create, truncate (outfile, here_doc)
// flag = 2: write, create, append (outfile if using here_doc)
static int	open_file(char *filename, int flag)
{
	int	fd;

	if (flag == 0)
		fd = open(filename, O_RDONLY, 0777);
	else if (flag == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    else if (flag == 2)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = -1;
	return (fd);
}

// read from stdin and write to .here_doc until the delimiter is entered
// return 0 if successful, otherwise return -1
int	set_here_doc(t_data *data)
{
	char	*line;
	int		fd;
	char	*limiter;

	limiter = ft_strjoin(data->argv[2], "\n");
	if (!limiter)
		return (-1);
	fd = open_file(".here_doc", 1);
	if (fd == -1)
		return (-1);
	ft_printf_fd(STDIN_FILENO, "here_doc > ");
	line = get_next_line(STDIN_FILENO);
	while (ft_strcmp(line, limiter) != 0)
	{
		ft_printf_fd(STDIN_FILENO, "here_doc > ");
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(limiter);
	close(fd);
	data->infile = ".here_doc";
	return (0);
}

// open the infile and handle errors
// unlink .here_doc if it was created
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
	if (ft_strcmp(data->infile, ".here_doc") == 0)
		if (unlink(".here_doc") == -1)
			return (err_msg("unlink .here_doc failed"), -1);
	return (0);
}

// if infile is .here_doc, open outfile in write, create, append mode
// otherwise open it in write, create, truncate mode
// return 0 if successful, otherwise return -1
int	set_outfile(t_data *data)
{
	if (ft_strcmp(data->infile, ".here_doc") == 0)
		data->out_fd = open_file(data->outfile, 2);
	else
		data->out_fd = open_file(data->outfile, 1);
	if (data->out_fd == -1)
		return (err_msg(data->outfile), -1);
	return (0);
}