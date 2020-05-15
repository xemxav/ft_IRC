//
// Created by Xavier-Emmanuel Moreau on 12/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

static void	init_fd(t_envc *e)
{
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	FD_SET(0, &e->fd_read);
	FD_SET(e->sock, &e->fd_read);
	if (e->circ.to_write)
		FD_SET(e->sock, &e->fd_write);
	e->max = max(0, e->sock);

}

static void	do_select(t_envc *e)
{
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 20;
	e->sel_ret = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
	//ajout except fd pour gerer les erreurs ?
}

static void	check_fd(t_envc *e)
{
	if(e->sel_ret > 0)
	{
		if (FD_ISSET(e->sock, &e->fd_read))
			e->fd.fct_read(e, e->sock);
		if (FD_ISSET(0, &e->fd_read))
			client_record(e);
		if (FD_ISSET(e->sock, &e->fd_write))
			e->fd.fct_write(e, e->sock);
	}
}

void run_client(t_envc *e)
{
	while (TRUE)
	{
		clean_input();
		print_prompt();
		init_fd(e);
		do_select(e);
		check_fd(e);
	}
}