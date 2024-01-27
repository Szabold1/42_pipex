#include "../include/pipex_bonus.h"

// print error message to stderr and exit with exit_code
// if msg is NULL, print error message based on errno
void	exit_err(char *msg, int exit_code)
{
	if (msg && errno)
		ft_printf_fd(2, "pipex: %s: %s\n", msg, strerror(errno));
	else if (msg)
		ft_printf_fd(2, "pipex: %s\n", msg);
	else if (errno)
		ft_printf_fd(2, "pipex: %s\n", strerror(errno));
	else
		ft_printf_fd(2, "pipex: error\n");
	exit(exit_code);
}

// print error message to stderr and return NULL
// if msg is NULL, print error message based on errno
char	*error(char *msg)
{
	if (msg && errno)
		ft_printf_fd(2, "pipex: %s: %s\n", msg, strerror(errno));
	else if (msg)
		ft_printf_fd(2, "pipex: %s\n", msg);
	else if (errno)
		ft_printf_fd(2, "pipex: %s\n", strerror(errno));
	else
		ft_printf_fd(2, "pipex: error\n");
	return (NULL);
}