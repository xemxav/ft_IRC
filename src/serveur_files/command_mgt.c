//
// Created by Xavier-Emmanuel Moreau on 06/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

const t_cmdl	g_cmd_tab[CMD_COUNT + 1] = {
		{PM, serv_pm},
		{CONNECT, serv_disconnect},
		{JOIN, serv_join},
		{LEAVE, serv_leave},
		{WRITE, serv_sel_write},
		{LIST, serv_list},
		{NICK, serv_nick},
		{WHO, serv_who},
		{NULL, NULL},
};

void 			serv_list(t_env *e, int cs)
{
	t_channel	*tmp;

	tmp = e->channels;
	clear_circ(&e->fds[cs].circ);
	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
	add_cmd(&e->fds[cs].circ, MINUS_LOG, 0);
	add_cmd(&e->fds[cs].circ, "The list of channel :", 0);
	while (tmp)
	{
		add_cmd(&e->fds[cs].circ, tmp->name, 0);
		tmp = tmp->next;
	}
	add_EOL(&e->fds[cs].circ);
}

void			serv_who(t_env *e, int cs)
{
	int			i;
	int 		c;

	i = 0;
	c = 0;
	clear_circ(&e->fds[cs].circ);
	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
	add_cmd(&e->fds[cs].circ, MINUS_LOG, 0);
	add_cmd(&e->fds[cs].circ, "The list of user of channel", 0);
	add_cmd(&e->fds[cs].circ, e->fds[cs].write_chan->name, 0);
	add_cmd(&e->fds[cs].circ, ":" , 0);
	while (i < e->max_fd)
	{
		if (i != cs && e->fds[i].write_chan == e->fds[cs].write_chan)
			add_cmd(&e->fds[cs].circ, e->fds[i].nick, 0);
		i++;
	}
	add_EOL(&e->fds[cs].circ);
}

void			serv_disconnect(t_env *e, int cs)
{
	int 		c;

	c = 0;
	printf("%s Client #%d has gone away\n",MINUS_LOG, cs);
	while (c < MAX_CHAN)
	{
		if (e->fds[cs].chan_bag[c] != NULL)
			leave_channel(e, e->fds[cs].chan_bag[c]);;
		c++;
	}
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
			free(cmd);
			return (g_cmd_tab[i].fct_cmd(e, cs));
		}
		i++;
	}
	send_back_serv_err(e, cs, "Unknow command", cmd);
	free(cmd);
}

