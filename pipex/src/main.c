/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:09:10 by bszabo            #+#    #+#             */
/*   Updated: 2024/02/08 12:09:12 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// check if arguments are valid
// return 0 if valid, otherwise return -1
static int	check_args(int argc)
{
	if (argc != 5)
		return (err_msg(ERR_ARGS_1), -1);
	if (environ == NULL)
		return (err_msg("env is empty"), -1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (err_msg("t_data allocation failed"), -1);
	if (check_args(argc) == -1)
		return (free(data), 2);
	if (init_data(argc, argv, data) == -1)
		return (clean_up(data), EXIT_FAILURE);
	if (set_data(data) == -1)
		return (clean_up(data), EXIT_FAILURE);
	if (exec_cmds(data) == -1)
		return (clean_up(data), EXIT_FAILURE);
	if (data->cmds[data->nb_cmds - 1]->path == NULL)
		return (clean_up(data), 127);
	clean_up(data);
	return (EXIT_SUCCESS);
}
