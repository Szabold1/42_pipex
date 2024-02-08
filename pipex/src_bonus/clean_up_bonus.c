/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:10:20 by bszabo            #+#    #+#             */
/*   Updated: 2024/02/08 12:10:23 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

// free a 2d array of strings and set it to NULL
static void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
	}
}

// free memory allocated for the commands
static void	free_cmds(t_data *data)
{
	int	i;

	i = 0;
	if (data->paths_arr)
	{
		free_array(data->paths_arr);
		data->paths_arr = NULL;
	}
	while (data->cmds && data->cmds[i] && i < data->nb_cmds)
	{
		if (data->cmds[i]->cmd_arr)
		{
			free_array(data->cmds[i]->cmd_arr);
			data->cmds[i]->cmd_arr = NULL;
		}
		if (data->cmds[i]->path)
		{
			free(data->cmds[i]->path);
			data->cmds[i]->path = NULL;
		}
		free(data->cmds[i]);
		data->cmds[i++] = NULL;
	}
	free(data->cmds);
	data->cmds = NULL;
}

// free memory allocated for the pipes
static void	free_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		if (data->pipes[i])
		{
			free(data->pipes[i]);
			data->pipes[i++] = NULL;
		}
	}
	free(data->pipes);
	data->pipes = NULL;
}

// close file descriptors (pipes, input and output)
void	close_fds(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
	if (data->in_fd != -1)
		close(data->in_fd);
	if (data->out_fd != -1)
		close(data->out_fd);
}

// clean up everything
void	clean_up(t_data *data)
{
	if (data)
	{
		close_fds(data);
		if (data->cmds)
		{
			free_cmds(data);
			data->cmds = NULL;
		}
		if (data->pipes)
		{
			free_pipes(data);
			data->pipes = NULL;
		}
		if (data->pids_child)
		{
			free(data->pids_child);
			data->pids_child = NULL;
		}
		free(data);
	}
}
