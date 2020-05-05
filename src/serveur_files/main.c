//
// Created by Xavier-Emmanuel Moreau on 23/04/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

static void	init_env(t_env *e, char *progname)
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

static void 	create_serveur(t_env *e, int port)
{
	int			s;
	struct sockaddr_in	sin;
	struct protoent	*pe;

	if ((pe = (struct protoent*)getprotobyname("tcp")) == NULL)
		error(e, "Could not get protocol");
	if ((s = socket(PF_INET, SOCK_STREAM, pe->p_proto)) == ERROR)
		error(e, "Could not create socket");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	if (bind(s, (struct sockaddr*)&sin, sizeof(sin)) == -1)
		error(e, "Could not bind");
	printf("%s Server is bound\n", PLUS_LOG);
	if (listen(s, 42) == -1)
		error(e, "Could not listen");
	printf("%s Server listen on port %d\n", PLUS_LOG, port);
	e->fds[s].type = FD_SERV;
	e->fds[s].fct_read = serveur_accept;
}

int main(int ac, char**av) {
	t_env e;
	int port;

	port = 0;
	if (ac < 2 || (port = ft_atoi(av[1])) == 0)
		usage(av[0], "<port>");
	init_env(&e, av[0]);
	create_serveur(&e, port);
	looping(&e);
	return (0);
}