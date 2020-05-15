//
// Created by Xavier-Emmanuel Moreau on 04/05/2020.
//

#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include "ft_irc.h"

# define USER "USER="
# define U_LEN 5

typedef struct 			s_envc
{
	char 				*host;
	t_fd 				fd;
	int 				max;
	int 				sel_ret;
	int					sock;
	int 				port;
	fd_set				fd_write;
	fd_set				fd_read;
	t_circ 				circ;
	int					serv_info;
	char 				*serv_name;
	char				nick[9];

}						t_envc;
/*
**				client_files/init_envc.c
*/
void					init_envc(t_envc *e, char **env);
void					run_session(t_envc *e);
/*
**				client_files/client_error.c
*/
void					client_error(t_envc *e, char *error);
/*
**				client_files/run_client.c
*/
void					run_client(t_envc *e);
/*
**				client_files/create_client.c
*/
void					create_client(t_envc *e);
/*
**				client_files/client_record.c
*/
void					print_prompt(void);
void					clean_screen(void);
void					clean_input(void);
void 					client_record(t_envc *e);
//int 					client_record(t_envc *e);



void					serveur_send(t_envc *e, int sock);
void					serveur_recv(t_envc *e, int sock);
#endif //FT_IRC_CLIENT_H
