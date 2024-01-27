#ifndef PIPEX_H
# define PIPEX_H

extern char **environ;

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "../libft/include/libft.h"

// FILE: errors.c
void	exit_err(char *msg, int exit_code);
char	*error(char *msg);
// FILE: execute.c
int 	execute(char *cmd);
int 	exec_cmd(char *cmd);
// File: file.c
int	    set_infile(char *infile);
int 	set_outfile(char *outfile);
// FILE: path.c
char	*get_path(char *cmd);
// FILE: pipex_utils.c
void	close_pipe(int fd_pipe[2]);
void	free_arr_of_strs(char **arr);
// FILE: pipex.c
int		main(int argc, char *argv[]);

#endif