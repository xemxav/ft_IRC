/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:40:30 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:49:44 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include "ft_irc.h"

# define USER "USER="
# define U_LEN 5
# define EXIT "/exit"

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
	char				*channel;
	char				nick[NICK_SIZE];

}						t_envc;
/*
**				client_files/init_envc.c
*/
void					init_envc(t_envc *e, char **env);
void					run_session(t_envc *e);
/*
**				client_files/client_exit.c
*/
void					client_error(t_envc *e, char *error);
void					clean_exit(t_envc *e);
void 					clean(t_envc *e);
/*
**				client_files/run_client.c
*/
int						run_client(t_envc *e);
/*
**				client_files/create_client.c
*/
void					create_client(t_envc *e);
/*
**				client_files/client_record.c
*/
void					print_prompt(t_envc *e);
void					clean_screen(void);
void					clean_input(void);
void 					client_record(t_envc *e);


void						serveur_send(t_envc *e, int sock);
/*
**				client_files/serveur_recv.c
*/
void					serveur_recv(t_envc *e, int sock);
/*
**				client_files/save_serveur_info.c
*/
void					save_server_info(t_envc *e);
void					first_message(t_envc *e);
void					change_chan_name(t_envc *e, char *cmd);


#endif //FT_IRC_CLIENT_H
