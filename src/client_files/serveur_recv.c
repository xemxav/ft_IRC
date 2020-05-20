/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_recv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:35:48 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:48:47 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

void		server_message(t_envc *e, char *prefix)
{
	t_circ	*circ;

	circ = &(e->fd.circ);
	clean_input();
	print_buf(circ);
	free(prefix);
}

void		channel_message(t_envc *e, char *channel)
{
	t_circ	*circ;
	char	*nick;

	circ = &(e->fd.circ);
	clean_input();
	nick = NULL;
	if ((nick = return_cmd(circ)) == NULL)
		client_error(e, "Could not get nick (channel message)");
	printf("\033[1;35m%s %s->\033[0m", channel, nick);
	print_buf(circ);
	free(channel);
	free(nick);
}

void		private_message(t_envc *e, char *private)
{
	t_circ	*circ;
	char	*nick;

	circ = &(e->fd.circ);
	clean_input();
	nick = NULL;
	if ((nick = return_cmd(circ)) == NULL)
		client_error(e, "Could not get command nick (private message)");
	printf("\033[1;36m%s (private) ->\033[0m", nick);
	print_buf(circ);
	free(private);
	free(nick);
}

void		analyse_transmission(t_envc *e)
{
	t_circ	*circ;
	char	*prefix;

	circ = &(e->fd.circ);
	if (!e->serv_info)
		return (save_server_info(e));
	if (circ->buf[circ->read_i] == ':' ||
	circ->buf[circ->read_i] == '#' || circ->buf[circ->read_i] == '/')
	{
		if ((prefix = return_cmd(circ)) == NULL)
			client_error(e, "Coudld not get prefix");
		if (ft_strncmp(e->serv_name, prefix, ft_strlen(e->serv_name)) == 0)
			return (server_message(e, prefix));
		else if (ft_strcmp("/write", prefix) == 0)
			return (change_chan_name(e, prefix));
		else if (ft_strcmp(PRIVATE, prefix) == 0)
			return (private_message(e, prefix));
		else if (prefix[0] == '#')
			return (channel_message(e, prefix));
		free(prefix);
	}
	else
		clear_circ(circ);
}

void		serveur_recv(t_envc *e, int sock)
{
	int		r;
	t_circ	*circ;

	circ = &(e->fd.circ);
	r = recv(sock, circ->buf + circ->write_i, CBS - circ->write_i, 0);
	if (r <= 0)
	{
		close(sock);
		clean_fd(&e->fd);
		client_error(e, "Serveur has disconnected");
	}
	else
	{
		circ->write_i += r;
		circ->data += r;
		circ->to_write = check_eol(circ);
		if (circ->to_write)
			analyse_transmission(e);
	}
}
