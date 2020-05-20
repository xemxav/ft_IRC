/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   serveur_send.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xem <xem@student.le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/05/20 15:35:52 by xem          #+#   ##    ##    #+#       */
/*   Updated: 2020/05/20 15:35:54 by xem         ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

void		reconnect(t_envc *e)
{
	t_circ	*circ;
	char	*port;

	circ = &e->circ;
	free(return_cmd(circ));
	if ((e->host  = return_cmd(circ)) == NULL)
		client_error(e, "Error while getting hostname");
	if ((port = return_cmd(circ)) == NULL)
		client_error(e, "Error while getting port");
	if ((e->port = ft_atoi(port)) == 0)
		client_error(e, "Error on port");
	free(port);
	clear_circ(circ);
	copy_to_buf(circ, CONNECT);
	if (send_buf(circ, e->sock) == ERROR)
		client_error(e, "Error while send buf");
	close(e->sock);
	clean_fd(&e->fd);
	free(e->fd.circ.buf);
	e->serv_info = 0;
	if (e->serv_name)
		free(e->serv_name);
	if (e->channel)
		free(e->channel);
	clean_screen();
	create_client(e);
}

void		exit_cmd(t_envc *e)
{
	t_circ	*circ;

	circ = &e->circ;
	clear_circ(circ);
	copy_to_buf(circ, CONNECT);
	if (send_buf(circ, e->sock) == ERROR)
		client_error(e, "Error while send buf");
	clean_exit(e);
}

void		check_cmd(t_envc *e)
{
	t_circ	*circ;

	circ = &e->circ;
	go_next_char(circ);
	if (cmp_cmd(circ, CONNECT))
		return (reconnect(e));
	if (cmp_cmd(circ, EXIT))
		exit_cmd(e);

}

void		serveur_send(t_envc *e, int sock)
{
	t_circ	*circ;

	circ = &e->circ;
	if (circ->buf[circ->read_i] == '/')
		check_cmd(e);
	if (send_buf(circ, sock) == ERROR)
		client_error(e, "Error while send buf");
}