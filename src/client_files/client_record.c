/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_record.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:32:29 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:48:27 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

void		clean_screen(void)
{
	ft_putstr("\033[2J\033[1;1H");
}

void		clean_input(void)
{
	ft_putstr("\033[2K");
	ft_putstr("\033[G");
}

void		print_prompt(t_envc *e)
{
	ft_putstr("\033[0;32m(");
	ft_putstr(e->channel);
	ft_putstr(") >>>\033[0m ");
}

void		client_record(t_envc *e)
{
	char	*line;
	t_circ	*circ;
	int		ret;

	circ = &e->circ;
	line = NULL;
	ret = get_next_line(0, &line);
	if (ret == -1)
		client_error(e, "Error while recording user input");
	if (line != NULL)
	{
		if (ft_strlen(line) == 0)
		{
			free(line);
			return ;
		}
		if (copy_to_buf(circ, line) != ft_strlen(line))
		{
			free(line);
			client_error(e, "Error while recording user input");
		}
		free(line);
	}
}
