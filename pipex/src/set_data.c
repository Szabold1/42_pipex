#include "../include/pipex.h"

// set all the data in t_data struct
// return 0 if successful, otherwise return -1
int	set_data(t_data *data)
{
	if (set_infile(data) == -1)
		return (-1);
	if (set_outfile(data) == -1)
		return (-1);
	if (set_cmds(data) == -1)
		return (-1);
	return (0);
}
