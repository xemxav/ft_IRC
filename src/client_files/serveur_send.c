/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_send.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:35:52 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:48:50 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

static void		clean_env(t_envc *e)
{
	clean_fd(&e->fd);
	if (e->fd.circ.buf)
	{
		free(e->fd.circ.buf);
		e->fd.circ.buf = NULL;
	}
	if (e->serv_name != NULL)
	{
		free(e->serv_name);
		e->serv_name = NULL;
	}
	if (e->channel != NULL)
	{
		free(e->channel);
		e->channel = NULL;
	}
	e->serv_info = 0;
}

int				reconnect(t_envc *e)
{
	char		*port;

	free(return_cmd(&e->circ));
	free(e->host);
	e->host = NULL;
	if ((e->host = return_cmd(&e->circ)) == NULL)
		client_error(e, "Error while getting hostname");
	if ((port = return_cmd(&e->circ)) == NULL)
		client_error(e, "Error while getting port");
	if ((e->port = ft_atoi(port)) == 0)
		client_error(e, "Error on port");
	free(port);
	clear_circ(&e->circ);
	copy_to_buf(&e->circ, CONNECT);
	if (send_buf(&e->circ, e->sock) == ERROR)
		client_error(e, "Error while send buf");
	close(e->sock);
	clean_env(e);
	return (STOP);
}

void			exit_cmd(t_envc *e)
{
	t_circ		*circ;

	circ = &e->circ;
	clear_circ(circ);
	copy_to_buf(circ, CONNECT);
	if (send_buf(circ, e->sock) == ERROR)
		client_error(e, "Error while send buf");
	clean_exit(e);
}

static int		check_cmd(t_envc *e)
{
	t_circ	*circ;

	circ = &e->circ;
	go_next_char(circ);
	if (cmp_cmd(circ, CONNECT))
		return (reconnect(e));
	if (cmp_cmd(circ, EXIT))
		exit_cmd(e);
	return (0);
}

int				serveur_send(t_envc *e, int sock)
{
	t_circ		*circ;

	circ = &e->circ;
	if (circ->buf[circ->read_i] == '/')
		if (check_cmd(e) == STOP)
			return (STOP);
	if (send_buf(circ, sock) == ERROR)
		client_error(e, "Error while send buf");
	return (TRUE);
}
