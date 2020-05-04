
#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

int		usage(char *prog_name,char *error)
{
	fprintf(stderr, "Usage :%s %s\n", prog_name, error);
	exit(ERROR);
}