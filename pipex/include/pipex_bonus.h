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

// FILE: errors_bonus.c
void	exit_err(char *msg, int exit_code);
char	*error(char *msg);
// FILE: execute_bonus.c
int		execute(char *cmd);
void	exec_cmd(char *cmd);
// File: file_bonus.c
int		set_infile(char *infile);
int		set_outfile(char *outfile);
// FILE: path_bonus.c
char	*get_path(char *cmd);
// FILE: pipex_bonus.c
int		main(int argc, char *argv[]);
// FILE: pipex_utils_bonus.c
void	close_pipe(int fd_pipe[2]);
void	free_arr_of_strs(char **arr);

#endif