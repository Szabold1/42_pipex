#ifndef PIPEX_H
# define PIPEX_H

# define ERR_ARGS_1 "Error: wrong number of arguments\n \
      Usage:	./pipex_bonus infile cmd1 cmd2 ... cmdn outfile\n \
		./pipex_bonus here_doc LIMITER cmd1 cmd2 ... cmdn outfile"

extern char **environ;

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include "../libft/include/libft.h"

// structure for data related to a single command
typedef struct s_cmd
{
	char	**cmd_arr;
	char	*path;
}	t_cmd;

// structure for all data related to pipex
typedef struct s_data
{
	char	**argv;
	char	*infile;
	char	*outfile;
	int		in_fd;
	int		out_fd;
	bool	skip_first_cmd;
	int		nb_cmds;
	char	**argv_cmd;
	char	**paths_arr;
	t_cmd	**cmds;
	int		**pipes;
	pid_t	*pids_child;
}	t_data;

// File: errors.c
void	err_msg(char *msg);
void	err_cmd(char *cmd);
// File: execute.c
int		exec_cmds(t_data *data);
// File: clean_up.c
void	close_fds(t_data *data);
void	clean_up(t_data *data);
// File: init_data.c
int		init_data(int argc, char *argv[], t_data *data);
// File: main.c
int		main(int argc, char **argv);
// File: set_data_cmds.c
int		set_cmds(t_data *data);
// File: set_data_files.c
int		set_here_doc(t_data *data);
int		set_infile(t_data *data);
int		set_outfile(t_data *data);
// File: set_data.c
int		set_data(t_data *data);

#endif