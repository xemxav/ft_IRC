
#include "../../includes/ft_irc.h"

int		usage(char *prog_name,char *error)
{
	if (error)
		fprintf(stderr, "Usage :%s %s\n", prog_name, error);
	else
		fprintf(stderr, "%s : une erreur s'est produite", prog_name);
	exit(ERROR);
}