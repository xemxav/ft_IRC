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
	ft_bzero(&e->circ, sizeof(t_circ));
	if ((e->circ.buf = (char*)malloc(CIRC_BUFF_SIZE)) == NULL)
		client_error(e, "Could not create buffer");
}

int main(int ac, char**av)
{
	int		port;
	t_envc	e;
	t_circ circ2;
	int eol;

	if (ac < 3 || (port = ft_atoi(av[2])) == 0)
		return (usage(av[0], "<host> <port>"));
	init_envc(&e, port, av);
	create_client(&e);
	while (1)
	{
		client_record(&e);
		ft_memcpy(&circ2, &e.circ, sizeof(t_circ));
		eol = check_EOL(&circ2);
//		if (eol)
//			printf("EOL ok %d\n", eol);
//		else
//			printf("EOL not ok %d\n", eol);
//		print_buf(&circ2);
		client_send(&e);
	}
	return (0);
}


