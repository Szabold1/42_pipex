#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "../libft/include/libft.h"

// FILE: execute.c
int		execute(char *cmd, char *envp[]);
void	exec_cmd(char *cmd, char *envp[]);
// FILE: errors.c
void	exit_err(char *msg, int exit_code);
char	*error(char *msg);
// FILE: path.c
char	*get_path(char *cmd, char *envp[]);
// FILE: pipex_utils.c
int		open_file(char *filename, int flag);
void	close_pipe(int fd_pipe[2]);
void	free_arr_of_strs(char **arr);
// FILE: pipex.c
int		main(int argc, char *argv[], char *envp[]);

#endif