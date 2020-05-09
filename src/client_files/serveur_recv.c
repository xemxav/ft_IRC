//
// Created by Xavier-Emmanuel Moreau on 07/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

void	serveur_recv(t_envc *e, int sock)
{
	int	r;
	t_circ *circ;

	circ = &(e->fd.circ);
	r = recv(sock, circ->buf + circ->write_i, CIRC_BUFF_SIZE - circ->write_i, 0);
	if (r <= 0)
	{
		close(sock);
		clean_fd(&e->fd);
		client_error(e, "Serveur has disconnected");
	}
	else
	{
		circ->write_i += r;
		circ->to_write = check_EOL(circ);
		if (circ->to_write)
		{
			clean_input(e);
			print_buf(circ);
		}

	}
}