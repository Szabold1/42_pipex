/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:10:29 by bszabo            #+#    #+#             */
/*   Updated: 2024/02/08 12:10:31 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
