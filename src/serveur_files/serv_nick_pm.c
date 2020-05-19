//
// Created by Xavier-Emmanuel Moreau on 15/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

static int	check_nick(t_env *e, int cs, char *nick)
{
	int 	i;

	i = 0;
	while (i < e->max_fd)
	{
		if (strcmp(e->fds[i].nick, nick) == 0)
		{
			send_back_serv_err(e, cs,
						"Your nick is already in use, "
						"please use a different one with /nick command", NULL);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void		serv_nick(t_env *e, int cs)
{
	char	*nick;
	ssize_t	len;

	if ((nick = return_cmd(&e->fds[cs].circ)) == NULL)
		error(e, "Could not find nick");
	if (nick[0] == '\0')
	{
		free(nick);
		send_back_serv_info(e, cs, "Please enter a nick, your actual nick is", e->fds[cs].nick);
		return;
	}
	if (check_nick(e, cs, nick))
	{
		len = ft_strlen(nick);
		len = min(len, 9);
		ft_memcpy(&e->fds[cs].nick, nick, len);
		send_back_serv_conf(e, cs, "Your nick has been changed to", nick);
		printf("%s sock %d has changed his nick to %s\n", PLUS_LOG, cs, nick);
	}
	else
		printf("%s sock %d could not change his nick to %s\n", ERR_LOG, cs, nick);
	free(nick);
}

static int	find_target_nick(t_env *e, int cs)
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
	send_back_serv_err(e, cs, "Could not find user", t_nick);
	return (ERROR);
}

void		serv_pm(t_env *e, int cs)
{
	int		nick_i;

	if ((nick_i = find_target_nick(e, cs)) == ERROR)
		return ;
	add_cmd(&e->fds[nick_i].circ, PRIVATE, 0);
	add_cmd(&e->fds[nick_i].circ, e->fds[cs].nick, 0);
	copy_buf(&e->fds[nick_i].circ, &e->fds[cs].circ);
	clear_circ(&e->fds[cs].circ);
}