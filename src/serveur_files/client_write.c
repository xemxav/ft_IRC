
#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void	client_write(t_env *e, int cs)
{
	t_circ	*circ;
	int 	data;

	circ = &e->fds[cs].circ;
	data = circ->data;
	if (send_buf(circ, cs) >= 0)
		printf("%s %d octets envoyées à sock #%d\n", PLUS_LOG, data, cs);
	else
		printf("%s N'avait rien a envoye a sock #%d mais rentrer dans client write\n", ERR_LOG, cs);
}
