#include "../include/pipex.h"

// check if arguments are valid
static void	check_args(int argc, char *envp[])
{
	if (argc != 5)
		error("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", true);
	if (envp[0] == NULL)
		error("env is empty\n", true);
}

// execute the first command and write the output to the pipe
static void	exec_cmd1(char *argv[], int *fd_pipe, char *envp[])
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(argv[1], 2);
		error(": No such file or directory (f: exec_cmd1)\n", true);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error("pipex: stdin -> infile failed (f: exec_cmd1)\n", true);
	close(fd_in);
	close(fd_pipe[0]);
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		error("pipex: stdout -> fd_pipe[1] failed (f: exec_cmd1)\n", true);
	execute(argv[2], envp);
}

// wait for the child process to finish
// read the result of the first command from the pipe
// execute the second command and write the output to the outfile
static void	exec_cmd2(char *argv[], int *fd_pipe, char *envp[])
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error("pipex: open outfile failed (f: exec_cmd2)\n", true);
	close(fd_pipe[1]);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		error("pipex: stdin -> fd_pipe[0] failed (f: exec_cmd2)\n", true);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		error("pipex: stdout -> outfile failed (f: exec_cmd2)\n", true);
	close(fd_out);
	execute(argv[3], envp);
}

// create a pipe
// create two separate processes for executing the two commands
int	main(int argc, char *argv[], char *envp[])
{
	int		fd_pipe[2];
	pid_t	pid;
	int		status;

	check_args(argc, envp);
	if (pipe(fd_pipe) == -1)
		error("pipex: create pipe failed (f: main)\n", true);
	pid = fork();
	if (pid == -1)
		error("pipex: fork() failed (f: main)\n", true);
	else if (pid == 0)
	{
		exec_cmd1(argv, fd_pipe, envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			error("waitpid() failed (f: main)\n", true);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		exec_cmd2(argv, fd_pipe, envp);
	}
}
