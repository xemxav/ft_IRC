//
// Created by Xavier-Emmanuel Moreau on 04/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

void 	clean_client(t_envc *e)
{
	close(e->sock);
	if (e->host)
		free(e->host);
	if (e->serv_name)
		free(e->serv_name);
	if (e->channel)
		free(e->channel);
	if (e->fd.circ.buf != NULL)
		free(e->fd.circ.buf);
	if (e->circ.buf != NULL)
		free(e->circ.buf);
}

void	clean_exit(t_envc *e)
{
	clean_client(e);
	clean_input();
	exit(TRUE);
}

void	client_error(t_envc *e, char *error)
{
	clean_input();
	clean_client(e);
	fprintf(stderr, "%s %s\n", ERR_LOG, error);
	exit(ERROR);
}