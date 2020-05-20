/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   serv_responses.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xem <xem@student.le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/05/20 15:37:49 by xem          #+#   ##    ##    #+#       */
/*   Updated: 2020/05/20 15:37:51 by xem         ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void 			send_back_serv_err(t_env *e, int cs, char *line, char *option)
{
	clear_circ(&e->fds[cs].circ);
	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
	add_cmd(&e->fds[cs].circ, ERR_LOG, 0);
	add_cmd(&e->fds[cs].circ, line, 0);
	if (option)
		add_cmd(&e->fds[cs].circ, option, 0);
	add_EOL(&e->fds[cs].circ);
}

void 			send_back_serv_info(t_env *e, int cs, char *line, char *option)
{
	clear_circ(&e->fds[cs].circ);
	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
	add_cmd(&e->fds[cs].circ, MINUS_LOG, 0);
	add_cmd(&e->fds[cs].circ, line, 0);
	if (option)
		add_cmd(&e->fds[cs].circ, option, 0);
	add_EOL(&e->fds[cs].circ);
}

void 			send_back_serv_conf(t_env *e, int cs, char *line, char *option)
{
	clear_circ(&e->fds[cs].circ);
	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
	add_cmd(&e->fds[cs].circ, PLUS_LOG, 0);
	add_cmd(&e->fds[cs].circ, line, 0);
	if (option)
		add_cmd(&e->fds[cs].circ, option, 0);
	add_EOL(&e->fds[cs].circ);
}