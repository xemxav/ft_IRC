/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:32:48 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:48:33 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

static int	get_nick(t_envc *e, char **env)
{
	while (env != NULL)
	{
		if (ft_strncmp(*env, USER, U_LEN) == 0)
		{
			ft_strncpy(e->nick, *env + U_LEN, NICK_SIZE);
			return (TRUE);
		}
		env++;
	}
	return (FALSE);
}

void		init_envc(t_envc *e, char **env)
{
	ft_bzero(e, sizeof(t_envc));
	e->circ.buf = (char*)malloc(CBS);
	if (e->circ.buf == NULL)
		client_error(e, "Could not create internal buffer");
	ft_bzero(e->circ.buf, CBS);
	if (!get_nick(e, env))
	{
		ft_memcpy(e->nick, "Guest", 5);
		printf("%s Could not find USER env variable\n", MINUS_LOG);
	}
}
