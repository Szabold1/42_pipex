#include "../include/pipex.h"

// check if arguments are valid
static void	check_args(int argc)
{
	if (argc != 5)
		exit_err("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile", EXIT_FAILURE);
	if (environ == NULL)
		exit_err("env is empty", EXIT_FAILURE);
}

// set infile to stdin and execute the first command
static void	first_pipe(char *argv[])
{
	if (set_infile(argv[1]) == -1)
		return ;
	exec_cmd(argv[2]);
}

// set outfile to stdout and execute the last command
static void	last_pipe(int argc, char *argv[])
{
	set_outfile(argv[argc - 1]);
	execute(argv[argc - 2]);
}

int	main(int argc, char *argv[])
{	
	check_args(argc);
	first_pipe(argv);
	last_pipe(argc, argv);
	exit(EXIT_FAILURE);
}