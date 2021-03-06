/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:32:37 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:48:31 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

static void				create_address_host(t_envc *e,
		struct sockaddr_in *target_addr)
{
	struct hostent		*host_info;
	struct in_addr		*address;
	char				*host;

	host_info = NULL;
	host = ft_strdup(e->host);
	host_info = gethostbyname(host);
	free(host);
	if (host_info == NULL)
		client_error(e, "Could not lookup hostname");
	address = (struct in_addr *)(host_info->h_addr);
	clean_input();
	printf("%s Has found host %s corresponding of %s at adress %s\n",
			PLUS_LOG, host_info->h_name, e->host, inet_ntoa(*address));
	target_addr->sin_addr = *((struct in_addr *)host_info->h_addr);
}

void					create_client(t_envc *e)
{
	struct sockaddr_in	target_addr;

	if ((e->sock = socket(PF_INET, SOCK_STREAM, 0)) == ERROR)
		client_error(e, "Could not create sock");
	ft_bzero(&target_addr, sizeof(struct sockaddr_in));
	target_addr.sin_family = AF_INET;
	target_addr.sin_port = htons(e->port);
	if (!ft_isdigit(*e->host))
		create_address_host(e, &target_addr);
	else
		target_addr.sin_addr.s_addr = inet_addr(e->host);
	if (connect(e->sock, (struct sockaddr *)&target_addr,
			sizeof(struct sockaddr)) == ERROR)
		client_error(e, "Could not connect to server");
	printf("%s Connected to server %s on port %d\n",
			PLUS_LOG, e->host, e->port);
	e->fd.type = FD_SERV;
	if ((e->fd.circ.buf = (char*)malloc(CBS)) == NULL)
		client_error(e, "Could not create fd buffer");
	ft_bzero(e->fd.circ.buf, CBS);
	e->fd.fct_read = serveur_recv;
	e->fd.fct_write = serveur_send;
}
