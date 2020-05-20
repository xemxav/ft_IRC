/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:37:37 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:49:10 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"


static void			init_envs(t_env *e, char *progname)
{
	struct rlimit	rlp;

	ft_bzero(e, sizeof(t_env));
	getrlimit(RLIMIT_NOFILE, &rlp);
	e->max_fd = rlp.rlim_cur;
	e->fds = (t_fd*)malloc(sizeof(t_fd) * e->max_fd);
	if (e->fds == NULL)
		usage(progname, "Could not create environnement");
	ft_bzero(e->fds, sizeof(t_fd) * e->max_fd);
	new_channel(e,DEFAULT_CHANNEL);
}



int					main(int ac, char**av)
{
	t_env			e;
	int				port;

	port = 0;
	if (ac < 2 || (port = ft_atoi(av[1])) == 0)
		usage(av[0], "<port>");
	init_envs(&e, av[0]);
	create_serveur(&e, port);
	looping(&e);
	return (0);
}