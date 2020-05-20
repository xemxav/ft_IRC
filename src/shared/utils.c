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

int			add_EOL(t_circ *circ)
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

int			check_EOL(t_circ *circ)
{
	int		i;
	int		check;
	int		match;

	i = EOL_SIZE;
	match = 0;
	while (i > 0)
	{
		check = circ->write_i - i;
		if (check < 0)
			check = CBS - check;
		if (circ->buf[check] == EOL[EOL_SIZE - i])
			match++;
		i--;
	}
	if (match == 2)
		return (TRUE);
	return (FALSE);
}