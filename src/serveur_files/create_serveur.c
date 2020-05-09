//
// Created by Xavier-Emmanuel Moreau on 06/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void 	create_serveur(t_env *e, int port)
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