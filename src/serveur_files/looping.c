//
// Created by Xavier-Emmanuel Moreau on 30/04/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

static void			init_fd(t_env *e)
{
	int				i;

	i = 0;
	e->max = 0;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	while (i < e->max_fd)
	{
		if (e->fds[i].type != FD_FREE)
		{
			FD_SET(i, &e->fd_read);
			if (e->fds[i].circ.to_write)
				FD_SET(i, &e->fd_write);
			e->max = max(e->max, i);
		}
		i++;
	}
}

static void			do_select(t_env *e)
{
	struct timeval	timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 20;
	e->sel_ret = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, &timeout);
}

static void			check_fd(t_env *e)
{
	int				i;

	i = 0;
	while ((i < e->max_fd) && (e->sel_ret > 0))
	{
		if (FD_ISSET(i, &e->fd_read))
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->fd_write))
			e->fds[i].fct_write(e, i);
		if (FD_ISSET(i, &e->fd_read) || FD_ISSET(i, &e->fd_write))
			e->sel_ret--;
		i++;
	}
}

void looping(t_env *e)
{
	while(TRUE)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
	}

}

