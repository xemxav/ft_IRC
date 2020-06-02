/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:38:10 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:49:20 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"

void	clean_fd(t_fd *fd)
{
	int	i;

	i = 0;
	fd->type = FD_FREE;
	fd->fct_read = NULL;
	fd->fct_write = NULL;
	fd->write_chan = NULL;
	ft_bzero(fd->nick, NICK_SIZE);
	while (i < MAX_CHAN)
	{
		fd->chan_bag[i] = NULL;
		i++;
	}
	fd->circ.to_write = 0;
	fd->circ.read_i = 0;
	fd->circ.write_i = 0;
	fd->circ.data = 0;
}
