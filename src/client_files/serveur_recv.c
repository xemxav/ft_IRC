//
// Created by Xavier-Emmanuel Moreau on 07/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

static void first_message(t_envc *e)
{
	t_circ *circ;

	circ = &(e->circ);
	add_cmd(circ, NICK, 0);
	copy_to_buf(circ, e->nick);
	send_buf(circ, e->sock);
}

void	save_server_info(t_envc *e)
{
	t_circ	*circ;
	char 	*sock;

	circ = &(e->fd.circ);
	if ((e->serv_name = return_cmd(circ)) == NULL)
		client_error(e, "Could not get Server Name");
	if ((sock = return_cmd(circ)) == NULL)
		client_error(e, "Could not get sock");
	if (ft_strncmp(e->nick, "Guest", 5) == 0)
		ft_strcat(e->nick, sock);
	e->serv_info = 1;
	free(sock);
	clean_input();
	print_buf(circ);
	first_message(e);
}

void		server_info(t_envc *e, char *prefix)
{
	t_circ	*circ;

	circ = &(e->fd.circ);
	clean_input();
	printf("%s ", PLUS_LOG);
	print_buf(circ);
	free(prefix);
}

void		channel_or_private(t_envc *e, char *nick)
{
	t_circ	*circ;
	char 	*cmd;


	circ = &(e->fd.circ);
	clean_input();
	cmd = NULL;
	if (circ->buf[circ->read_i] == '/')
	{
		if ((cmd = return_cmd(circ)) == NULL)
			client_error(e, "Could not get command (channel_or_private");
		if (ft_strncmp(cmd, PM, 4) == 0)
			printf("\033[1m%s (private) ->\033[0m ", nick +1);
	}
	else
		printf("\033[1m%s->\033[0m ", nick + 1);
	print_buf(circ);
	free(nick);
	free(cmd);
}

void		analyse_transmission(t_envc *e)
{
	t_circ	*circ;
	char	*prefix;

	circ = &(e->fd.circ);
	if (!e->serv_info)
		return(save_server_info(e));
	if (circ->buf[circ->read_i] == ':')
	{
		if ((prefix = return_cmd(circ)) == NULL)
			client_error(e, "Coudld not get prefix");
		if (ft_strncmp(e->serv_name, prefix, ft_strlen(e->serv_name)) == 0)
			return (server_info(e, prefix));
		else
			return (channel_or_private(e, prefix));
	}
	else
	{
		clean_input();
		printf("%s Received a message without prefix\n", ERR_LOG);
		print_buf(circ);
	}
}

void	serveur_recv(t_envc *e, int sock)
{
	int	r;
	t_circ *circ;

	circ = &(e->fd.circ);
	r = recv(sock, circ->buf + circ->write_i, CBS - circ->write_i, 0);
	if (r <= 0)
	{
		close(sock);
		clean_fd(&e->fd);
		client_error(e, "Serveur has disconnected");
	}
	else
	{
		circ->write_i += r;
		circ->data += r;
		circ->to_write = check_EOL(circ);
		if (circ->to_write)
			analyse_transmission(e);
	}
}