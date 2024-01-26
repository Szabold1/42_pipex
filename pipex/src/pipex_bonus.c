#include "../include/pipex.h"

// check if arguments are valid
static void	check_args(int argc, char *envp[])
{
	if (argc < 5)
		exit_err("Usage: ./pipex infile \"cmd1\" ... \"cmdn\" outfile", EXIT_FAILURE);
	if (envp[0] == NULL)
		exit_err("env is empty", EXIT_FAILURE);
}

void	set_infile(char *infile)
{
	int	fd_infile;

	fd_infile = open_file(infile, 0);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
	{
		close(fd_infile);
		exit_err(NULL, EXIT_FAILURE);
	}
	close(fd_infile);
}

void	set_outfile(char *outfile)
{
	int	fd_outfile;

	fd_outfile = open_file(outfile, 1);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		close(fd_outfile);
		exit_err(NULL, EXIT_FAILURE);
	}
	close(fd_outfile);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	i;

	i = 2;
	check_args(argc, envp);
	set_infile(argv[1]);
	while (i < argc - 2)
		exec_cmd(argv[i++], envp);
	set_outfile(argv[argc - 1]);
	execute(argv[argc - 2], envp);
	exit(EXIT_FAILURE);
}