

#ifndef FT_IRC_FT_IRC_H
#define FT_IRC_FT_IRC_H

#include "../libft/includes/libft.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct	s_env
{
	char				**args;
	int					sock;
	struct sockaddr_in	host_addr;
}				t_env;

typedef struct	s_client
{
	int 		sock;
	struct sockaddr_in	client_addr;
}				t_client;

int			usage(char *prog_name,char *error);

#endif
