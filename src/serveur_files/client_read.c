
#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void	client_read(t_env *e, int cs)
{
	int	r;
	t_circ *circ;

	circ = &e->fds[cs].circ;
	r = recv(cs, circ->buf + circ->write_i, CIRC_BUFF_SIZE - circ->write_i, 0);

	if (r <= 0) // de <= à < pour eviter que ca se coupe
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("%s Client #%d has gone away\n",MINUS_LOG, cs);
	}
	else
	{
		circ->write_i += r;
		circ->to_write = check_EOL(circ);
		if (circ->to_write)
			printf("%s recu %d octets de socket num %d -> pret a envoyer\n", PLUS_LOG, r, cs);
		else if (r > 0)
			printf("%s recu %d octets de socket num %d\n", MINUS_LOG, r, cs);
	}
}
