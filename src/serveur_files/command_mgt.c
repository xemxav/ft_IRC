//
// Created by Xavier-Emmanuel Moreau on 06/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

const t_cmdl	g_cmd_tab[CMD_COUNT + 1] = {
		{PM, serv_pm},
		{CONNECT, serv_disconnect},
		{JOIN, NULL},
		{NICK, serv_nick},
		{LIST, NULL},
		{NULL, NULL},
};

int			find_target_nick(t_env *e, int cs)
{
	int		i;
	char	*t_nick;

	i = 0;
	if ((t_nick = return_cmd(&e->fds[cs].circ)) == NULL)
		error(e, "Error on return cmd to find target nick");
	while (i < e->max_fd)
	{
		if(e->fds[i].type == FD_CLIENT && i != cs &&
		   ft_strncmp(e->fds[i].nick, t_nick, NICK_SIZE) == 0)
			return (i);
		i++;
	}
	clear_circ(&e->fds[cs].circ);
	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
	add_cmd(&e->fds[cs].circ, "Could not find user", 0);
	add_cmd(&e->fds[cs].circ, t_nick, 0);
	add_EOL(&e->fds[cs].circ);
	return (ERROR);
}

void serv_pm(t_env *e, int cs)
{
	int nick_i;

	if ((nick_i = find_target_nick(e, cs)) == ERROR)
		return ;
	add_cmd(&e->fds[nick_i].circ, e->fds[cs].nick, PREFIX);
	add_cmd(&e->fds[nick_i].circ, PM, 0);
	copy_buf(&e->fds[nick_i].circ, &e->fds[cs].circ);
	clear_circ(&e->fds[cs].circ);
}

void serv_disconnect(t_env *e, int cs)
{

	printf("%s Client #%d has gone away\n",MINUS_LOG, cs);
	leave_channel(e, e->fds[cs].channel);
	clean_fd(&e->fds[cs]);
	close(cs);
}

int	check_nick(t_env *e, int cs, char *nick)
{
	int i;

	i = 0;
	while (i < e->max_fd)
	{
		if (cs != i && strcmp(e->fds[i].nick, nick) == 0)
		{
			clear_circ(&e->fds[i].circ);
			add_cmd(&e->fds[cs].circ, S_NAME, ':');
			copy_to_buf(&e->fds[cs].circ,
				"Your nick is already in use, "
	"please use different one with /nick command");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	serv_nick(t_env *e, int cs)
{
	char *nick;
	ssize_t len;

	if ((nick = return_cmd(&e->fds[cs].circ)) == NULL) //todo modifier ce qui se passe
		error(e, "Could not find nick");
	if (check_nick(e, cs, nick))
	{
		len = ft_strlen(nick);
		len = min(len, 9);
		ft_memcpy(&e->fds[cs].nick, nick, len);
		clear_circ(&e->fds[cs].circ);
		add_cmd(&e->fds[cs].circ, S_NAME, ':');
		copy_to_buf(&e->fds[cs].circ, "Your nick has been change");
		printf("%s sock %d has changed his nick to %s\n", PLUS_LOG, cs, nick);
	}
	else
		printf("%s sock %d could not change his nick to %s\n", ERR_LOG, cs, nick);
	free(nick);
}

void	make_command(t_env *e, int cs)
{
	char *cmd;
	t_circ *circ;
	int i;

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

