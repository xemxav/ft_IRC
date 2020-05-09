//
// Created by Xavier-Emmanuel Moreau on 06/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

void	init_envc(t_envc *e, int port, char **av)
{
	ft_bzero(e, sizeof(t_envc));
	e->port = port;
	e->args = av;
	e->pr = 0;
	e->circ.buf = (char*)malloc(sizeof(CIRC_BUFF_SIZE));
	if (e->circ.buf == NULL)
		client_error(e, "Could not create internal buffer");
	clean_fd(&e->fd);
}