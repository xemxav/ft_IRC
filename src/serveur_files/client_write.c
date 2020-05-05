
#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void	client_write(t_env *e, int cs)
{
	t_circ	*circ;

	circ = &e->fds[cs].circ;
	printf("%s recu :", PLUS_LOG);
	print_buf(circ);
}
