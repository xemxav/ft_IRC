

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
#include <sys/time.h>

#define EOL "\r\n"
#define EOL_SIZE 2

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define CIRC_BUFF_SIZE	4096
# define DEFAULT_CHANNEL "#Public_Chatroom"
# define ERR_LOG "\033[0;31m[x]\033[0m"
# define PLUS_LOG "\033[0;32m[+]\033[0m"
# define MINUS_LOG "\033[0;33m[-]\033[0m"

typedef struct			s_circ
{
	char 				*buf;
	int 				write_i;
	int					read_i;
	int					to_write;
}						t_circ;


int						usage(char *prog_name,char *error);


int			recv_line(int sock, unsigned char *dest_buffer);


#endif
