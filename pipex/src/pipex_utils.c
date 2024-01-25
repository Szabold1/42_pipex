#include "../include/pipex.h"

// print error message with perror() and exit
void	*error(char *message, bool exit_program)
{
	if (message)
		ft_putstr_fd(message, 2);
	else
		ft_putstr_fd("pipex: error\n", 2);
	if (exit_program)
		exit(EXIT_FAILURE);
	else
		return NULL;
}

// loop through arr and free each string, then free arr
static void	free_arr_of_strs(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

// part of get_path()
// loop through paths and find the valid path of cmd
// return the valid path, or NULL if valid path is not found
static char	*get_valid_path(char **paths, char *cmd)
{
	int		i;
	char	*temp_path;
	char	*path;

	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		if (!temp_path)
			return (error("pipex: !temp_path (f: get_valid_path)\n", false));
		path = ft_strjoin(temp_path, cmd);
		if (!path)
		{
			free(temp_path);
			return (error("pipex: !path (f: get_valid_path)\n", false));
		}
		free(temp_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

// find the valid path of cmd
// return the valid path, or NULL if valid path is not found
// 1. find the PATH variable in envp
// 2. split the PATH variable into an array of strings
// 3. find the valid path of the command
static char	*get_path(char *cmd, char *envp[])
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	while (envp[i] && ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	if (!envp[i])
		return (error("pipex: PATH not found (f: get_path)\n", false));
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (error("pipex: split PATH failed (f: get_path)\n", false));
	path = get_valid_path(paths, cmd);
	if (!path)
	{
		free_arr_of_strs(paths);
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd, 2);
		return (error(": command not found (f: get_path)\n", false));
	}
	free_arr_of_strs(paths);
	return (path);
}

// execute the command 'cmd'
// 1. split 'cmd' into an array of strings
// 2. get the path of the command
// 3. execute the command
void	execute(char *cmd, char *envp[])
{
	char	**cmd_array;
	char	*path;

	cmd_array = ft_split(cmd, ' ');
	if (cmd_array == NULL)
		error("pipex: split cmd failed (f: execute)\n", true);
	path = get_path(cmd_array[0], envp);
	if (!path)
	{
		free_arr_of_strs(cmd_array);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd_array, envp) == -1)
		error("pipex: execve() failed (f: execute)\n", true);
}