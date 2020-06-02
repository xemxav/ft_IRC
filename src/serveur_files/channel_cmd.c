/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:36:15 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:48:55 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

char			*check_channel(t_env *e, int cs)
{
	char		*channel;

	channel = NULL;
	if ((channel = return_cmd(&e->fds[cs].circ)) == NULL)
		serveur_error(e, "Could not find channel name");
	if (channel[0] != '#')
	{
		free(channel);
		send_back_serv_err(e, cs, "The channel name must begin with #", NULL);
		return (NULL);
	}
	return (channel);
}

void			serv_join(t_env *e, int cs)
{
	char		*channel;
	int			c;

	if ((c = find_chan_index(e, cs)) >= MAX_CHAN - 1)
	{
		return (send_back_serv_err(e, cs, "You cannot join more than 5"
		" channels, you must '/leave [channel]' one first", NULL));
	}
	if ((channel = check_channel(e, cs)) == NULL)
		return ;
	if (find_channel_by_name(e, cs, channel) != ERROR)
	{
		return (send_back_serv_err(e, cs, "You cannot join a channel"
		" you have already joined", NULL));
	}
	clear_circ(&e->fds[cs].circ);
	e->fds[cs].chan_bag[c] = join_channel(e, channel);
	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
	add_cmd(&e->fds[cs].circ, PLUS_LOG, 0);
	add_cmd(&e->fds[cs].circ, "You have joined channel", 0);
	add_cmd(&e->fds[cs].circ, channel, 0);
	copy_to_buf(&e->fds[cs].circ,
			"to write on this channel use '/write <channel> command");
	free(channel);
}

void			serv_leave(t_env *e, int cs)
{
	char		*channel;
	int			c;

	if ((channel = check_channel(e, cs)) == NULL)
		return ;
	if ((c = find_channel_by_name(e, cs, channel)) != ERROR)
	{
		if (e->fds[cs].chan_bag[c] == e->fds[cs].write_chan)
			send_back_serv_info(e, cs,
		"You cannot leave your /write channel", NULL);
		else
		{
			leave_channel(e, e->fds[cs].chan_bag[c]);
			e->fds[cs].chan_bag[c] = NULL;
			send_back_serv_info(e, cs, "You have left the channel", channel);
		}
	}
	else
		send_back_serv_err(e, cs,
	"You cannot leave this unknown channel", channel);
	free(channel);
}

void			serv_sel_write(t_env *e, int cs)
{
	int			c;
	char		*channel;

	if ((channel = check_channel(e, cs)) == NULL)
		return ;
	if ((c = find_channel_by_name(e, cs, channel)) != ERROR)
	{
		e->fds[cs].write_chan = e->fds[cs].chan_bag[c];
		clear_circ(&e->fds[cs].circ);
		add_cmd(&e->fds[cs].circ, "/write", 0);
		copy_to_buf(&e->fds[cs].circ, channel);
	}
	else
		send_back_serv_err(e, cs, "You must join the channel first", NULL);
	free(channel);
}
