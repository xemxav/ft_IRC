
#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void	copy_buf(t_circ *dst, t_circ *src)
{
	int w;
	int r;

	printf("rentre dans copy buf\n");
	w = dst->write_i;
	r = src->read_i;
	if (dst->write_i != dst->read_i)
		printf("%s copy buf : le buffer contient deja des choses lors de la diffusion d'un message\n", ERR_LOG);
	while (r != src->write_i)
	{
		r = (r == CIRC_BUFF_SIZE) ? 0 : r;
		w = (w == CIRC_BUFF_SIZE) ? 0 : w;
		dst->buf[w] = src->buf[r];
		dst->data++;
		r++;
		w++;
	}
	dst->write_i = w;
	dst->to_write = TRUE;
}

void	diffuse_msg(t_env *e, int cs)
{
	int	i;

	i = 0;
	printf("rentre dans diffuse message\n");
	if (e->fds[cs].channel == NULL)
		error(e, "The client is not in a channel");
	while (i < e->max_fd)
	{
		if(e->fds[i].type == FD_CLIENT && i != cs && e->fds[i].channel == e->fds[cs].channel)
			copy_buf(&e->fds[i].circ, &e->fds[cs].circ);
		i++;
	}
	e->fds[cs].circ.read_i = e->fds[cs].circ.write_i;
	e->fds[cs].circ.to_write = 0;
}

void 	message_rooting(t_env *e, int cs)
{
	t_circ *circ;

	circ = &e->fds[cs].circ;
	if (circ->buf[circ->read_i] == '/')
		make_command(e, cs);
	else
		diffuse_msg(e, cs);
}

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
		{
			printf("%s recu %d octets de socket num %d complet\n", MINUS_LOG, r, cs);
			message_rooting(e, cs);
		}
		else if (r > 0)
			printf("%s recu %d octets de socket num %d\n", MINUS_LOG, r, cs);
	}
}
