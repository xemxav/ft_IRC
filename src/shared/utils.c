/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:38:28 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:49:28 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"

int			max(int a, int b)
{
	return ((a > b) ? a : b);
}

int			min(int a, int b)
{
	return ((a < b) ? a : b);
}

size_t		add_eol(t_circ *circ)
{
	int i;

	i = 0;
	while (i < EOL_SIZE)
	{
		circ->buf[circ->write_i] = EOL[i];
		inci(&circ->write_i);
		i++;
	}
	circ->to_write = 1;
	circ->data += 2;
	return (circ->data);
}

int			check_eol(t_circ *circ)
{
	int		i;

	i = circ->write_i;
	if (i > 1 && circ->buf[i - 1] == EOL[1] && circ->buf[i - 2] == EOL[0])
		return (TRUE);
	if (i == 1 && circ->buf[0] == EOL[1] && circ->buf[CBS - 1] == EOL[0])
		return (TRUE);
	if (i == 0 && circ->buf[CBS - 1] == EOL[1] && circ->buf[CBS - 2] == EOL[0])
		return (TRUE);
	return (FALSE);
}
