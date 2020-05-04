
#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void	client_read(t_env *e, int cs)
{
	int	r;
	int	i;
	t_circ *circ;

	circ = &e->fds[cs].circ;
	r = recv(cs, &circ->buf[circ->write_i], CIRC_BUFF_SIZE - circ->write_i, 0);
	circ->write_i += r;
	if (circ->buf[circ->write_i - 1] == EOL[1] &&
			circ->buf[circ->write_i - 2] == EOL[0])
		circ->to_write = 1;
	if (r < 0) // de <= à < pour eviter que ca se coupe
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("%sClient #%d had gone away\n",MINUS_LOG, cs);
	}
	else
	{
		i = 0;
//		while (i < e->max_fd) //envoie le message a tous les autres clients
//		{
//			if ((e->fds[i].type == FD_CLIENT) && (i != cs))
//				send(i, e->fds[cs].buf_read, r, 0);
//			i++;
//		}
		if (circ->to_write)
			printf("%srecu %d octets de socket num %d -> pret a envoyer\n", PLUS_LOG, r, cs);
		else if (r > 0)
			printf("%srecu %d octets de socket num %d\n", MINUS_LOG, r, cs);
	}
}
