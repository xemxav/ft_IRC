//
// Created by Xavier-Emmanuel Moreau on 18/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

int 			find_chan_index(t_env *e, int cs)
{
	int 		c;

	c = 0;
	while (c < MAX_CHAN)
	{
		if (e->fds[cs].chan_bag[c] == NULL)
			return (c);
		c++;
	}
	return (c);
}

char			*check_channel(t_env *e, int cs)
{
	char		*channel;

	channel = NULL;
	if ((channel = return_cmd(&e->fds[cs].circ)) == NULL)
		error(e, "Could not find channel name");
	if (channel[0] != '#')
	{
		free(channel);
		send_back_serv_err(e, cs, "The channel name must begin with #", NULL);
		return (NULL);
	}
	return (channel);
}

void 			serv_join(t_env *e, int cs)
{
	char		*channel;
	int 		c;

	if ((c = find_chan_index(e, cs)) > MAX_CHAN - 1)
		return (send_back_serv_err(e, cs, "You cannot join more than 5 channels,"
									  " you must '/leave [channel]' one first", NULL));
	if ((channel = check_channel(e, cs)) == NULL)
		return;
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

void 			serv_leave(t_env *e, int cs)
{
	char		*channel;
	int 		c;

	c = 0;
	if ((channel = check_channel(e, cs)) == NULL)
		return;
	while (c < MAX_CHAN)
	{
		if (e->fds[cs].chan_bag[c] != NULL && strcmp(e->fds[cs].chan_bag[c]->name, channel) == 0)
		{
			leave_channel(e, e->fds[cs].chan_bag[c]);
			e->fds[cs].chan_bag[c] = NULL;
			send_back_serv_info(e, cs, "You have left the channel", channel);
			free(channel);
			return;
		}
		c++;
	}
	send_back_serv_err(e, cs, "You cannot leave tis unknown channel", channel);
	free(channel);
}

void 			serv_sel_write(t_env *e, int cs)
{
	int 		c;
	char 		*channel;


	c = 0;
	if ((channel = check_channel(e, cs)) == NULL)
		return;
	while (c < MAX_CHAN)
	{
		if (e->fds[cs].chan_bag[c] != NULL &&
		strcmp(e->fds[cs].chan_bag[c]->name, channel) == 0)
		{
			e->fds[cs].write_chan = e->fds[cs].chan_bag[c];
			free(channel);
			clear_circ(&e->fds[cs].circ);
			add_cmd(&e->fds[cs].circ, "/write", 0);
			copy_to_buf(&e->fds[cs].circ, channel);
			return;
		}
		c++;
	}
	send_back_serv_err(e, cs, "You must join the channel first", NULL);
	free(channel);
}