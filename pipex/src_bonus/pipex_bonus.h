#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft.h"

// FILE: pipex_bonus_utils.c
void	error(char *message);
void	execute(char *cmd, char *envp[]);

#endif