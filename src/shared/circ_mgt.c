/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_mgt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:38:05 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:49:18 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"

int			send_buf(t_circ *circ, int sock)
{
	int		to_send;
	int		ret;

	if (circ->read_i == circ->write_i)
	{
		circ->to_write = 0;
		return (TRUE);
	}
	if (circ->read_i < circ->write_i)
		to_send = circ->write_i - circ->read_i;
	else
		to_send = CBS - circ->read_i;
	if ((ret = send(sock, circ->buf + circ->read_i, to_send, 0)) == ERROR)
		return (ERROR);
	circ->read_i += ret;
	if (circ->read_i == CBS)
		circ->read_i = 0;
	circ->data -= ret;
	return (send_buf(circ, sock));
}

int			print_buf(t_circ *circ)
{
	int		to_print;
	char	*s;

	if (circ->write_i == circ->read_i)
	{
		circ->to_write = FALSE;
		return (TRUE);
	}
	if (circ->read_i < circ->write_i)
		to_print = circ->write_i - circ->read_i;
	else
		to_print = CBS - circ->read_i;
	if ((s = ft_strsub(circ->buf, circ->read_i, to_print)) == NULL)
		return (ERROR);
	ft_putstr(s);
	free(s);
	circ->read_i += to_print;
	if (circ->read_i == CBS)
		circ->read_i = 0;
	circ->data -= to_print;
	return (print_buf(circ));
}

size_t		copy_to_buf(t_circ *circ, char *line)
{
	while (*line)
	{
		circ->buf[circ->write_i] = *line;
		inci(&circ->write_i);
		circ->data++;
		line++;
	}
	return (add_eol(circ - EOL_SIZE));
}
