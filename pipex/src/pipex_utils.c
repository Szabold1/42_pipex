#include "../include/pipex.h"

// print error message with perror() and exit
void	error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

// loop through arr and free each string, then free arr
void	free_arr_of_strs(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

// loop through paths and find the valid path of cmd
// return the valid path, or NULL if valid path is not found
char	*get_valid_path(char **paths, char *cmd)
{
	int		i;
	char	*temp_path;
	char	*path;

	i = 0;
	while (paths[i])
	{
		// add '/' to the end of paths[i]
		temp_path = ft_strjoin(paths[i], "/");
		if (!temp_path)
			error("ft_strjoin(paths[i], \"/\") failed\n");
		// add cmd to the end of temp_path
		path = ft_strjoin(temp_path, cmd);
		if (!path)
			error("ft_strjoin(temp_path, cmd) failed\n");
		free(temp_path);
		// check if path is valid
		if (access(path, F_OK) == 0)
		{
			free_arr_of_strs(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_arr_of_strs(paths);
	return (NULL);
}

// find the valid path of cmd
// return the valid path, or NULL if valid path is not found
char	*get_path(char *cmd, char *envp[])
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	// find the PATH variable in envp
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	// split the PATH variable into an array of strings
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		error("ft_split(envp[i] + 5, ':') failed\n");
	// get the valid path of the command
	path = get_valid_path(paths, cmd);
	return (path);
}

// execute the command 'cmd'
void	execute(char *cmd, char *envp[])
{
	char	**cmd_array;
	char	*path;

	// split cmd into an array of strings
	cmd_array = ft_split(cmd, ' '); // {"ls", "-la", NULL}
	if (cmd_array == NULL)
		error("split cmd into an array of strings failed\n");
	// get the path of the command
	path = get_path(cmd_array[0], envp);
	if (!path)
	{
		free_arr_of_strs(cmd_array);
		error("get_path() failed\n");
	}
	// execute the command
	if (execve(path, cmd_array, envp) == -1)
		error("execve() failed\n");
}