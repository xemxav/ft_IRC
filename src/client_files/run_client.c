/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   run_client.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xem <xem@student.le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/05/20 15:33:02 by xem          #+#   ##    ##    #+#       */
/*   Updated: 2020/05/20 15:33:04 by xem         ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

static void	init_fd(t_envc *e)
{
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	FD_SET(0, &e->fd_read);
	FD_SET(e->sock, &e->fd_read);
	if (e->circ.to_write)
		FD_SET(e->sock, &e->fd_write);
	e->max = max(0, e->sock);

}

static void	do_select(t_envc *e)
{
	e->sel_ret = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
}

static void	check_fd(t_envc *e)
{
	if(e->sel_ret > 0)
	{
		if (FD_ISSET(e->sock, &e->fd_read))
			e->fd.fct_read(e, e->sock);
		if (FD_ISSET(0, &e->fd_read))
			client_record(e);
		if (FD_ISSET(e->sock, &e->fd_write))
			e->fd.fct_write(e, e->sock);
	}
}

int			run_client(t_envc *e)
{
	while (TRUE)
	{
		clean_input();
		print_prompt(e);
		init_fd(e);
		do_select(e);
		check_fd(e);
	}
}