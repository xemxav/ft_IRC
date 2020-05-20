/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:36:26 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:49:01 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void		client_write(t_env *e, int cs)
{
	t_circ	*circ;
	int		data;

	circ = &e->fds[cs].circ;
	data = circ->data;
	if (send_buf(circ, cs) >= 0)
		printf("%s %d octets envoyées à sock #%d\n", PLUS_LOG, data, cs);
	else
		printf("%s N'avait rien a envoye a sock"
		 " #%d mais rentrer dans client write\n", ERR_LOG, cs);
}
