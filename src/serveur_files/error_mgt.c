//
// Created by Xavier-Emmanuel Moreau on 30/04/2020.
//

#include "../../includes/ft_irc.h"

void 		free_fds(t_env *e)
{
	free(e->fds);
}

void		error(t_env *e, char *error)
{
	if (e->fds != NULL)
		free_fds(e);
	fprintf(stderr, "%s\n", error);
	exit(EXIT_FAILURE);
}