#include "../include/pipex.h"

// check if arguments are valid
static void	check_args(int argc, char *envp[])
{
    if (envp[0] == NULL)
        error("env is empty\n");
    if (argc < 5)
        error("Usage: ./pipex infile \"cmd1\" ... \"cmdn\" outfile\n");
}

// open a file named 'filename' and return the file descriptor of the file
// flag = 0: read only (infile)
// flag = 1: write only (outfile)
static int	open_file(char *filename, int flag)
{
    int fd;

    if (flag == 0)
        fd = open(filename, O_RDONLY, 0777);
    else if (flag == 1)
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd == -1)
        error("open_file() failed\n");
    return (fd);
}

// execute the command 'cmd', and write the output to the created pipe
// set stdin to the read end of pipe, so next time we can read from the pipe
static void	exec_cmd(char *cmd, char *envp[])
{
    int     fd_pipe[2];
    pid_t   pid;

    if (pipe(fd_pipe) == -1)
        error("create pipe failed\n");
    pid = fork();
    if (pid == -1)
        error("fork failed\n");
    else if (pid == 0)
    {
        close(fd_pipe[0]);
        if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
            error("make write end of pipe the new stdout failed\n");
        execute(cmd, envp);
    }
    else
    {
        wait(NULL);
        close(fd_pipe[1]);
        if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
            error("make read end of pipe the new stdin failed\n");
    }
}

// open infile and set it to stdin
// execute commands, except the last one
// open outfile and set it to stdout
// execute the last command
int	main(int argc, char *argv[], char *envp[])
{
    int i;
    int fd_in;
    int fd_out;

    check_args(argc, envp);
    fd_in = open_file(argv[1], 0);
    if (dup2(fd_in, STDIN_FILENO) == -1)
        error("make infile the new stdin failed\n");
    close(fd_in);
    i = 2;
    while (i < argc - 2)
        exec_cmd(argv[i++], envp);
    fd_out = open_file(argv[argc - 1], 1);
    if (dup2(fd_out, STDOUT_FILENO) == -1)
        error("make outfile the new stdout failed\n");
    close(fd_out);
    execute(argv[argc - 2], envp);
}