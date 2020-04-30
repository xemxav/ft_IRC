

#ifndef FT_IRC_FT_IRC_H
#define FT_IRC_FT_IRC_H

#include "../libft/includes/libft.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netdb.h>

#define EOL "\r\n"
#define EOL_SIZE 2

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define CIRC_BUFF_SIZE	4096

typedef struct			s_circ
{
	char 				*buffer;
	char				*read;
	char 				*write
}						t_circ;

typedef struct			s_fd
{
	int					type;
	void				(*fct_read)();
	void				(*fct_write)();
	struct s_circ		buf;
}						t_fd;

typedef struct			s_env
{
	char				**args;
	int					sock;
	t_fd 				*fds;
	int					max_fd;
	int 				max;
	int 				sel_ret;
	fd_set				write;
	fd_set				read;
]}						t_env;



int						usage(char *prog_name,char *error);
void 					error(t_env *e, char *error);
void					free_fds(t_env *e);

void				 	create_serveur(t_env *e, int port);
void 					serveur_accept(t_env *e, int s);
int			recv_line(int sock, unsigned char *dest_buffer);

void					client_read(t_env *e, int cs);
void					client_write(t_env *e, int cs);

void					check_fd(t_env *e);
void					clean_fd(t_fd *fd);
#endif
