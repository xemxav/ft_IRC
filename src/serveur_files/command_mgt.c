//
// Created by Xavier-Emmanuel Moreau on 06/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

const t_cmdl	g_cmd_tab[CMD_COUNT + 1] = {
		{PM, serv_pm},
		{CONNECT, serv_disconnect},
		{JOIN, serv_join},
		{NICK, serv_nick},
		{LIST, serv_list},
		{NULL, NULL},
};

void			serv_list(t_env *e, int cs)
{
	int			i;

	i = 0;
	clear_circ(&e->fds[cs].circ);
	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
	add_cmd(&e->fds[cs].circ, "The list of user of channel", 0);
	add_cmd(&e->fds[cs].circ, e->fds[cs].channel->name , 0);
	add_cmd(&e->fds[cs].circ, ":" , 0);
	while (i < e->max_fd)
	{
		if (i != cs && e->fds[i].channel == e->fds[cs].channel)
			add_cmd(&e->fds[cs].circ, e->fds[i].nick, 0);
		i++;
	}
	add_EOL(&e->fds[cs].circ);
}

void 			send_back_error(t_env *e, int cs)
{

	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
	copy_to_buf(&e->fds[cs].circ, "The channel name must begin with #");
}

void 			serv_join(t_env *e, int cs)
{
	char *channel;

	if ((channel = return_cmd(&e->fds[cs].circ)) == NULL)
		error(e, "Could not find channe name");
	clear_circ(&e->fds[cs].circ);
	if (channel[0] != '#')
	{
		free(channel);
		return (send_back_error(e, cs));
	}
	e->fds[cs].channel = join_channel(e, e->fds[cs].channel, channel);
	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
	add_cmd(&e->fds[cs].circ, "You have joined channel", 0);
	add_cmd(&e->fds[cs].circ, channel, 0);
	add_EOL(&e->fds[cs].circ);
	free(channel);
}

void			serv_disconnect(t_env *e, int cs)
{

	printf("%s Client #%d has gone away\n",MINUS_LOG, cs);
	leave_channel(e, e->fds[cs].channel);
	clean_fd(&e->fds[cs]);
	close(cs);
}

void			make_command(t_env *e, int cs)
{
	char		*cmd;
	t_circ		*circ;
	int			i;

	circ = &e->fds[cs].circ;
	i = 0;
	if ((cmd = return_cmd(circ)) == NULL)
		error(e, "Could not get command from message");
	while (g_cmd_tab[i].cmd_name)
	{
		if (ft_strcmp(g_cmd_tab[i].cmd_name, cmd) == 0)
		{
			if (g_cmd_tab[i].fct_cmd != NULL) //todo : a enlever
				g_cmd_tab[i].fct_cmd(e, cs);
			break;
		}
		i++;
	}
	free(cmd);
}

