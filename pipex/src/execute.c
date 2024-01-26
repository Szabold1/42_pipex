#include "../include/pipex.h"

// execute the command 'cmd'
// 1. split 'cmd' into an array of strings
// 2. get the path of the command
// 3. execute the command
int	execute(char *cmd, char *envp[])
{
	char	**cmd_array;
	char	*path;

	cmd_array = ft_split(cmd, ' ');
	if (cmd_array == NULL)
		exit_err("cmd_array is NULL (f: execute)", EXIT_FAILURE);
	path = get_path(cmd_array[0], envp);
	if (!path)
	{
		free_arr_of_strs(cmd_array);
		return (EXIT_SUCCESS);
	}
	if (execve(path, cmd_array, envp) == -1)
		exit_err(NULL, EXIT_FAILURE);
	free_arr_of_strs(cmd_array);
	return (EXIT_FAILURE);
}

static void	exec_cmd_child(int fd_pipe[2], char *cmd, char *envp[])
{
	close(fd_pipe[0]);
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
	{
		close(fd_pipe[1]);
		exit_err(NULL, EXIT_FAILURE);
	}
	if (execute(cmd, envp) != EXIT_SUCCESS)
	{
		close(fd_pipe[1]);
		exit_err(NULL, EXIT_FAILURE);
	}
	close(fd_pipe[1]);
	exit(EXIT_SUCCESS);
}

static void	exec_cmd_parent(int fd_pipe[2], pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
	{
		close_pipe(fd_pipe);
		exit(WEXITSTATUS(status));
	}
	close(fd_pipe[1]);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
	{
		close(fd_pipe[0]);
		exit_err(NULL, EXIT_FAILURE);
	}
}

void	exec_cmd(char *cmd, char *envp[])
{
    int		fd_pipe[2];
    pid_t	pid;

    if (pipe(fd_pipe) == -1)
		exit_err(NULL, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		close_pipe(fd_pipe);
		exit_err(NULL, EXIT_FAILURE);
	}
	else if (pid == 0)
		exec_cmd_child(fd_pipe, cmd, envp);
	else
		exec_cmd_parent(fd_pipe, pid);
}