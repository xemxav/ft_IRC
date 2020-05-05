//
// Created by Xavier-Emmanuel Moreau on 30/04/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void free_fds(t_env *e)
{
	int i;

	i = 0;
	while (i <= e->max_fd)
	{
		if (e->fds[i].circ.buf != NULL)
			free(e->fds[i].circ.buf);
		i++;
	}
	free(e->fds);
}

void		error(t_env *e, char *error)
{
	if (e->fds != NULL)
		free_fds(e);
	if (e->channels != NULL)
		free_channels(e->channels);
	fprintf(stderr, "%s %s\n", ERR_LOG, error);
	exit(EXIT_FAILURE);
}