//
// Created by Xavier-Emmanuel Moreau on 04/05/2020.
//

#ifndef FT_IRC_SERVEUR_H
#define FT_IRC_SERVEUR_H

#include "ft_irc.h"

typedef	struct			s_channel
{
	char 				*name;
	int 				p;
	struct s_channel	*next;
}						t_channel;

typedef struct			s_fd
{
	int					type;
	void				(*fct_read)();
	void				(*fct_write)();
	struct s_circ		circ;
	char				nick[9];
	struct s_channel	*channel;
}						t_fd;

typedef struct			s_env
{
	char				**args;
	int					sock;
	t_fd 				*fds;
	int					max_fd;
	int 				max;
	int 				sel_ret;
	fd_set				fd_write;
	fd_set				fd_read;
	struct s_channel	*channels;
}						t_env;

/*
**				serveur_files/error_mgt.c
*/
void 					error(t_env *e, char *error);
void					free_fds(t_env *e);
/*
**				serveur_files/serveur_accept.c
*/
void 					serveur_accept(t_env *e, int s);
void					clean_fd(t_fd *fd);
/*
**				serveur_files/channel_mgt.c
*/
t_channel				*new_channel(t_env *e, char *name);
t_channel				*free_channels(t_channel *head);
void 					delete_channel(t_env *e, t_channel *channel);
t_channel 				*leave_channel(t_env *e, t_channel *current);
t_channel				*join_channel(t_env *e, t_channel *cur, char *c_name);
/*
**				serveur_files/client_read.c
*/
void					client_read(t_env *e, int cs);
/*
**				serveur_files/client_write.c
*/
void					client_write(t_env *e, int cs);
/*
**				serveur_files/looping.c
*/
void 					looping(t_env *e);

#endif //FT_IRC_SERVEUR_H