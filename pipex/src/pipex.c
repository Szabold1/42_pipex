#include "../include/pipex.h"

// execute the first command and write the output to the pipe
void	child_process(char *argv[], int *fd_pipe, char *envp[])
{
	int	fd_in;

	// open infile
	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in == -1)
		error("open infile failed\n");
	// make infile the new stdin
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error("make infile the new stdin failed\n");
	close(fd_in);
	// close unused end of pipe (read)
	close(fd_pipe[0]);
	// make write end of pipe the new stdout
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		error("make write end of pipe the new stdout failed\n");
	// execute the first command
	execute(argv[2], envp);
}

// wait for the child process to finish
// read the result of the first command from the pipe
// execute the second command and write the output to the outfile
void	parent_process(char *argv[], int *fd_pipe, char *envp[])
{
	int	fd_out;

	wait(NULL);
	// open outfile
	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error("open outfile failed\n");
	// close unused end of pipe (write)
	close(fd_pipe[1]);
	// make read end of pipe the new stdin
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		error("make read end of pipe the new stdin failed\n");
	// make outfile the new stdout
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		error("make outfile the new stdout failed\n");
	close(fd_out);
	// execute the second command
	execute(argv[3], envp);
}

// create a pipe for passing first command's output to second command's input
// create two separate processes for executing the two commands
int	main(int argc, char *argv[], char *envp[])
{
	int		fd_pipe[2];
	pid_t	pid;

	if (argc != 5)
		error("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
	// create pipe
	if (pipe(fd_pipe) == -1)
		error("create pipe failed\n");
	// create fork
	pid = fork();
	if (pid == -1)
		error("fork() failed\n");
	else if (pid == 0)
		child_process(argv, fd_pipe, envp);
	else
		parent_process(argv, fd_pipe, envp);
}