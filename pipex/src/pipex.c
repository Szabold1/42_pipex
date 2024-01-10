#include "pipex.h"

// check if arguments are valid
static void	check_args(int argc, char *envp[])
{
	if (argc != 5)
		error("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
	if (envp[0] == NULL)
		error("env is empty\n");
}

// execute the first command and write the output to the pipe
static void	exec_cmd1(char *argv[], int *fd_pipe, char *envp[])
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in == -1)
		error("open infile failed\n");
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error("make infile the new stdin failed\n");
	close(fd_in);
	close(fd_pipe[0]);
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		error("make write end of pipe the new stdout failed\n");
	execute(argv[2], envp);
}

// wait for the child process to finish
// read the result of the first command from the pipe
// execute the second command and write the output to the outfile
static void	exec_cmd2(char *argv[], int *fd_pipe, char *envp[])
{
	int	fd_out;

	wait(NULL);
	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error("open outfile failed\n");
	close(fd_pipe[1]);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		error("make read end of pipe the new stdin failed\n");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		error("make outfile the new stdout failed\n");
	close(fd_out);
	execute(argv[3], envp);
}

// create a pipe
// create two separate processes for executing the two commands
int	main(int argc, char *argv[], char *envp[])
{
	int		fd_pipe[2];
	pid_t	pid;

	check_args(argc, envp);
	if (pipe(fd_pipe) == -1)
		error("create pipe failed\n");
	pid = fork();
	if (pid == -1)
		error("fork() failed\n");
	else if (pid == 0)
		exec_cmd1(argv, fd_pipe, envp);
	else
		exec_cmd2(argv, fd_pipe, envp);
}