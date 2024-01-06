#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"


// FILE: pipex_utils.c
void	error(const char *message);
void	execute(char *cmd, char *envp[]);

#endif