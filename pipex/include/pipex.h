#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "../libft/include/libft.h"

// FILE: pipex_utils.c
void	*error(char *message, bool exit_program);
void	execute(char *cmd, char *envp[]);

#endif