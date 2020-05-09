//
// Created by Xavier-Emmanuel Moreau on 04/05/2020.
//

#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include "ft_irc.h"

typedef struct 			s_envc
{
	char				**args;
	t_fd 				fd;
	int					max_fd;
	int 				max;
	int 				sel_ret;
	int					sock;
	int 				port;
	fd_set				fd_write;
	fd_set				fd_read;
	t_circ 				circ;
	int					pr;
}						t_envc;
/*
**				client_files/init_envc.c
*/
void					init_envc(t_envc *e, int port, char **av);
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
void					print_prompt(t_envc *e);
void					clean_input(t_envc *e);
int 					client_record(t_envc *e);
void					serveur_send(t_envc *e, int sock);
void					serveur_recv(t_envc *e, int sock);
#endif //FT_IRC_CLIENT_H
