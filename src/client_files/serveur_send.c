//
// Created by Xavier-Emmanuel Moreau on 07/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

void 	check_cmd(t_envc *e)
{
	t_circ *circ;
	char 	*port;

	circ = &e->circ;
	go_next_char(circ);
	if (cmp_cmd(circ, CONNECT))
	{

		if (send_buf(circ, e->sock) == ERROR)
			client_error(e, "Error while send buf");
		free(return_cmd(circ));
		close(e->sock);
		free(e->host);
		if ((e->host = return_cmd(circ)) == NULL)
			client_error(e, "Error while getting hostname");
		if ((port = return_cmd(circ)) == NULL)
			client_error(e, "Error while getting hostname");
		if ((e->port = ft_atoi(port)) == 0)
			client_error(e, "Error on port");
		free(port);
		run_session(e);
	}
}

void	serveur_send(t_envc *e, int sock)
{
	t_circ *circ;

	circ = &e->circ;
	if (circ->buf[circ->read_i] == '/')
		check_cmd(e);
	if (send_buf(circ, sock) == ERROR)
		client_error(e, "Error while send buf");
}