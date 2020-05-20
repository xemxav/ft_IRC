/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_mgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:38:16 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:49:22 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/ft_irc.h"

void		clear_circ(t_circ *circ)
{
	circ->data = 0;
	circ->read_i = circ->write_i;
	circ->to_write = 0;
}

int			inci(int *i)
{
	*i = (*i + 1 == CBS) ? 0 : *i + 1;
	return (*i);
}

int			dont_stop(char *buf, int i)
{
	int		next;

	if (buf[i] == ' ' || buf[i] == 0)
		return (FALSE);
	next = (i == CBS - 1) ? 0 : i + 1;
	if (buf[i] == EOL[0] && buf[next] == EOL[1])
		return (FALSE);
	return (TRUE);
}