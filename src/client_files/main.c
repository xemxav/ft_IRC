//
// Created by Xavier-Emmanuel Moreau on 23/04/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

static void	init_envc(t_envc *e, int port, char **av)
{
	ft_bzero(e, sizeof(t_envc));
	e->port = port;
	e->args = av;
	e->circ.buf = (char*)malloc(CIRC_BUFF_SIZE);
	if (e->circ.buf == NULL)
		client_error(e, "Could not create buffer");
}

int main(int ac, char**av)
{
	int		port;
	t_envc	e;

	if (ac < 3 || (port = ft_atoi(av[2])) == 0)
		return (usage(av[0], "<host> <port>"));
	init_envc(&e, port, av);
	create_client(&e);

	return (0);
}