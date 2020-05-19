//
// Created by Xavier-Emmanuel Moreau on 07/05/2020.
//

#include "../../includes/ft_irc.h"

void	clean_fd(t_fd *fd)
{
	int	i;

	i = 0;
	fd->type = FD_FREE;
	fd->fct_read = NULL;
	fd->fct_write = NULL;
	fd->write_chan = NULL;
	while (i < MAX_CHAN)
	{
		fd->chan_bag[i] = NULL;
		i++;
	}
	clear_circ(&fd->circ);
}
