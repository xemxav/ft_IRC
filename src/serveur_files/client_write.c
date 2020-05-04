
#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void	client_write(t_env *e, int cs)
{
	t_circ	*circ;

	circ = &e->fds[cs].circ;
	printf("%s recu : %s\n", PLUS_LOG, &circ->buf[circ->write_i]);
	circ->write_i = circ->read_i;
	circ->to_write = FALSE;
}
