/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:08:33 by bszabo            #+#    #+#             */
/*   Updated: 2024/02/08 12:08:36 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// fill up all the t_cmd structs with initial values
// return 0 if successful, otherwise return -1
static int	init_cmds(t_data *data)
{
	int	i;

	i = 0;
	data->cmds = (t_cmd **)malloc(sizeof(t_cmd *) * (data->nb_cmds + 1));
	if (data->cmds == NULL)
		return (err_msg("data->cmds malloc failed"), -1);
	while (i < data->nb_cmds)
	{
		data->cmds[i] = (t_cmd *)malloc(sizeof(t_cmd));
		if (data->cmds[i] == NULL)
			return (err_msg("data->cmds[i] malloc failed"), -1);
		data->cmds[i]->cmd_arr = NULL;
		data->cmds[i]->path = NULL;
		i++;
	}
	data->cmds[i] = NULL;
	return (0);
}

// initialize pipes array and create pipes
// return 0 if successful, otherwise return -1
static int	init_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->pipes = (int **)malloc(sizeof(int *) * (data->nb_cmds - 1));
	if (!data->pipes)
		return (err_msg("pipes malloc failed"), -1);
	while (i < data->nb_cmds - 1)
	{
		data->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			return (err_msg("pipes[i] malloc failed"), -1);
		if (pipe(data->pipes[i]) == -1)
			return (err_msg("pipes[i] creating pipe failed"), -1);
		i++;
	}
	return (0);
}

// initialize pids_child array with initial values
// return 0 if successful, otherwise return -1
static int	init_pids_child(t_data *data)
{
	int	i;

	i = 0;
	data->pids_child = (pid_t *)malloc(sizeof(pid_t) * data->nb_cmds);
	if (data->pids_child == NULL)
		return (err_msg("data->pids_child malloc failed"), -1);
	while (i < data->nb_cmds)
	{
		data->pids_child[i] = -1;
		i++;
	}
	return (0);
}

// initialize data that needs allocated memory
// return 0 if successful, otherwise return -1
static int	init_memory(t_data *data)
{
	if (init_cmds(data) == -1)
		return (err_msg("init_cmds failed"), -1);
	if (init_pipes(data) == -1)
		return (err_msg("init_pipes failed"), -1);
	if (init_pids_child(data) == -1)
		return (err_msg("init_pids_child failed"), -1);
	return (0);
}

// fill up t_data struct with initial values
// return 0 if successful, otherwise return -1
int	init_data(int argc, char *argv[], t_data *data)
{
	data->argv = argv;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->in_fd = -1;
	data->out_fd = -1;
	data->skip_first_cmd = false;
	data->nb_cmds = argc - 3;
	data->argv_cmd = &argv[2];
	data->paths_arr = NULL;
	if (init_memory(data) == -1)
		return (err_msg("init_memory failed"), -1);
	return (0);
}
