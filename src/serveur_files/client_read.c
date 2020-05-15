
#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void	copy_buf(t_circ *dst, t_circ *src, int s)
{
	int w;
	int r;

	w = dst->write_i;
	r = src->read_i;
	while (r != src->write_i)
	{
		dst->buf[w] = src->buf[r];
		dst->data++;
		inci(&r);
		inci(&w);
	}
	dst->write_i = w;
	dst->to_write = TRUE;
}

void	diffuse_msg(t_env *e, int cs)
{
	int	i;

	i = 0;
	if (e->fds[cs].channel == NULL)
		error(e, "The client is not in a channel");
	while (i < e->max_fd)
	{
		if(e->fds[i].type == FD_CLIENT && i != cs &&
		e->fds[i].channel == e->fds[cs].channel)
		{
			add_cmd(&e->fds[i].circ, e->fds[cs].nick, PREFIX);
			copy_buf(&e->fds[i].circ, &e->fds[cs].circ, i);
		}
		i++;
	}
	clear_circ(&e->fds[cs].circ);
}

void 	message_rooting(t_env *e, int cs)
{
	t_circ *circ;

	circ = &e->fds[cs].circ;
	go_next_char(circ);
	if (e->fds[cs].nick[0] == '\0')
	{
		if (circ->buf[circ->read_i] != '/' && cmp_cmd(circ, NICK) == FALSE)
		{
			clear_circ(circ);
			add_cmd(circ, S_NAME, PREFIX);
			copy_to_buf(circ, "You must chose a nick");
			return;
		}
	}
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
	r = recv(cs, circ->buf + circ->write_i, CBS - circ->write_i, 0);
	if (r <= 0) // de <= à < pour eviter que ca se coupe
		serv_disconnect(e, cs);
	else
	{
		circ->write_i += r;
		circ->data += r;
		circ->to_write = check_EOL(circ);
		if (circ->to_write)
		{
			printf("%s recu %d octets de socket num %d complet\n", PLUS_LOG, r, cs);
			message_rooting(e, cs);
		}
		else if (r > 0)
			printf("%s recu %d octets de socket num %d\n", MINUS_LOG, r, cs);
	}
}
