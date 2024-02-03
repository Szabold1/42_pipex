#include "../include/pipex.h"

// execute the command 'cmd'
// 1. split 'cmd' into an array of strings
// 2. get the path of the command
// 3. execute the command
int	execute(char *cmd)
{
	char	**cmd_array;
	char	*path;

	cmd_array = ft_split(cmd, ' ');
	if (cmd_array == NULL)
	{
		ft_printf_fd(2, "pipex: %s\n", strerror(errno));
		return (-1);
	}
	path = get_path(cmd_array[0]);
	if (!path)
	{
		free_arr_of_strs(cmd_array);
		return (0);
	}
	if (execve(path, cmd_array, environ) == -1)
	{
		ft_printf_fd(2, "pipex: %s\n", strerror(errno));
		free_arr_of_strs(cmd_array);
		free(path);
		return (-1);
	}
	return (-1);
}

// set write end of pipe to stdout and execute the command 'cmd'
static int	exec_cmd_child(int fd_pipe[2], char *cmd)
{
	close(fd_pipe[0]);
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
	{
		close(fd_pipe[1]);
		return (-1);		
	}
	if (execute(cmd) == -1)
	{
		close(fd_pipe[1]);
		return (-1);
	}
	close(fd_pipe[1]);
	return (0);
}

// set read end of pipe to stdin, so that the next command can read from it
static int	exec_cmd_parent(int fd_pipe[2], pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
	{
		close_pipe(fd_pipe);
		return (WEXITSTATUS(status));
	}
	close(fd_pipe[1]);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
	{
		close(fd_pipe[0]);
		return (-1);
	}
	close(fd_pipe[0]);
	return (0);
}

// create a child process to execute the command 'cmd'
// parent process sets the pipe for next command
int	exec_cmd(char *cmd)
{
    int		fd_pipe[2];
    pid_t	pid;

    if (pipe(fd_pipe) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close_pipe(fd_pipe);
		return (-1);
	}
	else if (pid == 0)
		return (exec_cmd_child(fd_pipe, cmd));
	else
		return (exec_cmd_parent(fd_pipe, pid));
}