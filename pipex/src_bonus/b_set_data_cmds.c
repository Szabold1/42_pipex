#include "../include/pipex_bonus.h"

// check if the cmd is an absolute path
// if yes, set path and return 0, if not, return -1
static int	check_abs_path(t_cmd *cmd_d)
{
	char	*cmd;

	cmd = cmd_d->cmd_arr[0];
	if (access(cmd, F_OK) == 0)
	{
		cmd_d->path = ft_strdup(cmd);
		if (!cmd_d->path)
			return (err_msg("ft_strdup failed"), -1);
		return (0);
	}
	return (-1);
}

// join path with command and return the result (using malloc)
static char	*join_cmd_path(char *path, char *cmd)
{
	char	*temp_path;
	char	*path_cmd;

	path_cmd = NULL;
	temp_path = ft_strjoin(path, "/");
	if (temp_path == NULL)
		return (err_msg("ft_strjoin failed"), NULL);
	path_cmd = ft_strjoin(temp_path, cmd);
	free(temp_path);
	if (path_cmd == NULL)
		return (err_msg("ft_strjoin failed"), NULL);
	return (path_cmd);
}

// set valid path for a single command
// if valid path is found, set cmd_d->path and return 0, if not, return -1
static int	set_cmd_path(t_data *data, t_cmd *cmd_d)
{
	int		i;
	char	*temp_path;

	i = 0;
	temp_path = NULL;
	while (data->paths_arr[i])
	{
		temp_path = join_cmd_path(data->paths_arr[i], cmd_d->cmd_arr[0]);
		if (temp_path == NULL)
			return (err_msg("join_cmd_path failed"), -1);
		if (access(temp_path, F_OK) == 0)
		{
			cmd_d->path = ft_strdup(temp_path);
			if (cmd_d->path == NULL)
				return (err_msg("ft_strdup failed"), -1);
			free(temp_path);
			return (0);
		}
		free(temp_path);
		i++;
	}
	return (-1);
}

// set paths_arr with PATH environment variable
// if PATH is not found or env is empty, set paths_arr to NULL
// if successful, return 0, otherwise return -1
int	set_paths_arr(t_data *data)
{
	int		i;

	i = 0;
	while (environ[i] && ft_strncmp("PATH=", environ[i], 5) != 0)
		i++;
	if (environ[i] == NULL)
	{
		data->paths_arr = (char **)malloc(sizeof(char *));
		if (data->paths_arr == NULL)
			return (err_msg("paths_arr malloc failed"), -1);
		data->paths_arr[0] = NULL;
	}
	else
	{
		data->paths_arr = ft_split(environ[i] + 5, ':');
		if (data->paths_arr == NULL)
			return (err_msg("paths_arr split failed"), -1);
	}
	return (0);
}

// set values for all commands (cmd_arr, path)
// if all commands are set, return 0, otherwise return -1
int	set_cmds(t_data *data)
{
	int		i;

	i = 0;
	if (data->skip_first_cmd)
		i = 1;
	if (set_paths_arr(data) == -1)
		return (-1);
	while (i < data->nb_cmds)
	{
		data->cmds[i]->cmd_arr = ft_split(data->argv_cmd[i], ' ');
		if (data->cmds[i]->cmd_arr == NULL)
			return (err_msg("cmd_arr split failed"), -1);
		if (check_abs_path(data->cmds[i]) == 0)
		{
			i++;
			continue ;
		}
		if (set_cmd_path(data, data->cmds[i]) == -1)
			err_cmd(data->cmds[i]->cmd_arr[0]);
		i++;
	}
	return (0);
}
