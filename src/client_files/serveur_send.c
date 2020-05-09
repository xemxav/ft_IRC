//
// Created by Xavier-Emmanuel Moreau on 07/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

void	serveur_send(t_envc *e, int sock) {
	t_circ *circ;

//	printf("rentre dans serveur_recv %d\n", e->etape++);
	circ = &e->circ;
	if (send_buf(circ, sock) == ERROR)
		client_error(e, "Error while send buf");
}