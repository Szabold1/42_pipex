#include "../include/pipex_bonus.h"

// check if the given 'cmd' is an absolute path
static char *check_abs_path(char *cmd)
{
	char *path;

	path = NULL;
	if (access(cmd, F_OK) == 0)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (error("path is NULL (f: get_path)"));
	}
	return (path);
}

// part of get_path()
// loop through 'paths' and find the valid path of 'cmd'
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
			return (error("temp_path is NULL (f: get_valid_path)"));
		path = ft_strjoin(temp_path, cmd);
		if (!path)
		{
			free(temp_path);
			return (error("path is NULL (f: get_valid_path)"));
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
 char	*get_path(char *cmd)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	paths = NULL;
	path = check_abs_path(cmd);
	if (path)
		return (path);
	while (environ[i] && ft_strncmp("PATH", environ[i], 4) != 0)
		i++;
	if (!environ[i])
		return (error(cmd));
	paths = ft_split(environ[i] + 5, ':');
	if (!paths)
		return (error("split PATH failed (f: get_path)"));
	path = get_valid_path(paths, cmd);
	if (!path)
	{
		free_arr_of_strs(paths);
		ft_printf_fd(2, "pipex: %s: command not found\n", cmd);
		return (NULL);
	}
	free_arr_of_strs(paths);
	return (path);
}
