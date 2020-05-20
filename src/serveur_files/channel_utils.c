/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:36:19 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:48:57 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

int				find_chan_index(t_env *e, int cs)
{
	int			c;

	c = 0;
	while (c < MAX_CHAN)
	{
		if (e->fds[cs].chan_bag[c] == NULL)
			return (c);
		c++;
	}
	return (c);
}

int				find_channel_by_name(t_env *e, int cs, char *channel)
{
	int			c;

	c = 0;
	while (c < MAX_CHAN)
	{
		if (e->fds[cs].chan_bag[c] != NULL &&
			strcmp(e->fds[cs].chan_bag[c]->name, channel) == 0)
			return (c);
		c++;
	}
	return (ERROR);
}
