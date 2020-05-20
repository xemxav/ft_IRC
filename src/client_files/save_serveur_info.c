/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_serveur_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:33:09 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:48:45 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

void		first_message(t_envc *e)
{
	t_circ	*circ;

	circ = &(e->circ);
	add_cmd(circ, NICK, 0);
	copy_to_buf(circ, e->nick);
	send_buf(circ, e->sock);
}

void		save_server_info(t_envc *e)
{
	t_circ	*circ;
	char	*sock;

	circ = &(e->fd.circ);
	if ((e->serv_name = return_cmd(circ)) == NULL)
		client_error(e, "Could not get Server Name");
	if ((sock = return_cmd(circ)) == NULL)
		client_error(e, "Could not get sock");
	if (ft_strncmp(e->nick, "Guest", 5) == 0)
		ft_strcat(e->nick, sock);
	if ((e->channel = return_cmd(circ)) == NULL)
		client_error(e, "Could not get channel name");
	e->serv_info = 1;
	free(sock);
	clean_input();
	print_buf(circ);
	first_message(e);
}

void		change_chan_name(t_envc *e, char *cmd)
{
	t_circ	*circ;

	circ = &(e->fd.circ);
	free(cmd);
	free(e->channel);
	if ((e->channel = return_cmd(circ)) == NULL)
		client_error(e, "Could not get channel name");
	clear_circ(circ);
}
