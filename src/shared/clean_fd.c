//
// Created by Xavier-Emmanuel Moreau on 07/05/2020.
//

#include "../../includes/ft_irc.h"

void	clean_fd(t_fd *fd)
{
	fd->type = FD_FREE;
	fd->fct_read = NULL;
	fd->fct_write = NULL;
	fd->channel = NULL;
}
