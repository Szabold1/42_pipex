#include "../include/pipex_bonus.h"

// set stdin and stdout to the right pipes, if it fails, exit
static void	set_std_in_out(int std_in, int std_out, t_data *data)
{
	if (dup2(std_in, STDIN_FILENO) == -1
		|| dup2(std_out, STDOUT_FILENO) == -1)
	{
		err_msg(NULL);
		clean_up(data);
		exit(EXIT_FAILURE);
	}
}

// handle the case where infile is invalid,
// and the first command should be skipped
void	handle_skip_first_cmd(t_data *data, int i)
{
	if (i == 1 && data->nb_cmds == 2)
			set_std_in_out(data->in_fd, data->out_fd, data);
	else if (i == 1)
		set_std_in_out(data->in_fd, data->pipes[i][1], data);
	else if (i == data->nb_cmds - 1)
		set_std_in_out(data->pipes[i - 1][0], data->out_fd, data);
	else
		set_std_in_out(data->pipes[i - 1][0], data->pipes[i][1], data);
}

// execute a single command
// if it fails, return -1, otherwise it won't return because of execve
static void	exec_cmd(t_data *data, int i)
{
	if (data->skip_first_cmd)
		handle_skip_first_cmd(data, i);
	else
	{
		if (i == 0)
			set_std_in_out(data->in_fd, data->pipes[i][1], data);
		else if (i == data->nb_cmds - 1)
			set_std_in_out(data->pipes[i - 1][0], data->out_fd, data);
		else
			set_std_in_out(data->pipes[i - 1][0], data->pipes[i][1], data);
	}
	close_fds(data);
	if (data->cmds[i]->path != NULL)
		execve(data->cmds[i]->path, data->cmds[i]->cmd_arr, environ);
	clean_up(data);
	exit(EXIT_FAILURE);
}

// wait for all child processes to finish
static int	wait_for_childs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds && data->pids_child[i] > 0)
		waitpid(data->pids_child[i++], NULL, 0);
	return (0);
}

// execute all commands
// return 0 if successful, otherwise return -1
int	exec_cmds(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	if (data->skip_first_cmd)
		i = 1;
	while (i < data->nb_cmds)
	{
		pid = fork();
		if (pid == -1)
			return (err_msg("fork failed"), -1);
		else if (pid == 0)
			exec_cmd(data, i);
		else
			data->pids_child[i] = pid;
		i++;
	}
	close_fds(data);
	wait_for_childs(data);
	return (0);
}
