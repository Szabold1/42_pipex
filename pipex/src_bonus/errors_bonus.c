#include "../include_bonus/pipex_bonus.h"

void	err_msg(char *msg)
{
	ft_printf_fd(STDERR_FILENO, "pipex: ");
	if (msg && errno)
		perror(msg);
	else if (msg)
		ft_printf_fd(STDERR_FILENO, "%s\n", msg);
	else if (errno)
		perror(NULL);
	else
		ft_printf_fd(STDERR_FILENO, "error\n");
}

void	err_cmd(char *cmd)
{
	if (cmd)
		ft_printf_fd(STDERR_FILENO, "pipex: %s: command not found\n", cmd);
	else
		ft_printf_fd(STDERR_FILENO, "pipex: error\n");
}
