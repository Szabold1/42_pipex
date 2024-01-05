// fcntl.h: open()
// stdlib.h: exit()
// unistd.h: fork(), dup2(), close(), STDIN_FILENO
// stdio.h: perror()
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

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