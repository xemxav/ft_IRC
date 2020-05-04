//
// Created by Xavier-Emmanuel Moreau on 04/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

void	client_error(t_envc *e, char *error)
{
	if (e->circ.buf != NULL)
		free(e->circ.buf);
	fprintf(stderr, "%s %s\n", ERR_LOG, error);
	exit(ERROR);
}