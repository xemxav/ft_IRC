//
// Created by Xavier-Emmanuel Moreau on 04/05/2020.
//

#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include "ft_irc.h"

typedef struct 			s_envc
{
	char				**args;
	int 				port;
	int					sock;
	struct s_circ		circ;

}						t_envc;

/*
**				client_files/client_error.c
*/
void					client_error(t_envc *e, char *error);
/*
**				client_files/create_client.c
*/
void					create_client(t_envc *e);
/*
**				client_files/client_send.c
*/
int						client_send(t_envc *e);
int 					client_record(t_envc *e);
#endif //FT_IRC_CLIENT_H
