
#include "../../includes/ft_irc.h"

int		usage(char *prog_name,char *error)
{
	fprintf(stderr, "Usage :%s %s\n", prog_name, error);
	exit(ERROR);
}