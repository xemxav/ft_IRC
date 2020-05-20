/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_accept.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:37:54 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:49:15 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

static void					new_chan_bag(t_env *e, int cs)
{
	e->channels->p++;
	e->fds[cs].write_chan = e->channels;
	e->fds[cs].chan_bag[0] = e->channels;
}

void						serveur_accept(t_env *e, int s)
{
	int						cs;
	struct sockaddr_in		csin;
	socklen_t				csin_len;
	char					*sock;

	csin_len = sizeof(csin);
  	if ((cs = accept(s, (struct sockaddr*)&csin, &csin_len)) == ERROR)
  		 serveur_error(e,"Error on accept");
  	printf("%s New client #%d from %s:%d\n", PLUS_LOG, cs,
  			inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
  	clean_fd(&e->fds[cs]);
  	e->fds[cs].type = FD_CLIENT;
  	e->fds[cs].fct_read = client_read;
  	e->fds[cs].fct_write = client_write;
  	ft_bzero(&e->fds[cs].circ, sizeof(t_circ));
  	if ((e->fds[cs].circ.buf = (char*)malloc(CBS)) == NULL)
		serveur_error(e, "Client Buffer Creation");
	new_chan_bag(e, cs);
  	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
  	if ((sock = ft_itoa(cs)) == NULL)
  		serveur_error(e, "Coudl not create client socket");
  	add_cmd(&e->fds[cs].circ, sock, 0);
  	free(sock);
  	copy_to_buf(&e->fds[cs].circ, "#Public_Chatroom Welcome to the serveur, "
							 "you are connected on channel #Public_Chatroom");
  	send_buf(&e->fds[cs].circ, cs);
}

