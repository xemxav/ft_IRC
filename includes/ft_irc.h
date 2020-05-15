

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

# define NICK_SIZE  9
# define S_NAME "ft_irc"
# define PREFIX ':'
# define SN_LEN 6

# define CBS	4096
# define MAXLEN 510
# define MAXLEN_EOL MAXLEN + EOL_SIZE
# define DEFAULT_CHANNEL "#Public_Chatroom"
# define ERR_LOG "\033[0;31m[x]\033[0m"
# define PLUS_LOG "\033[0;32m[+]\033[0m"
# define MINUS_LOG "\033[0;33m[-]\033[0m"

#define SP 0x20
# define PM "/msg"
# define CONNECT "/connect"
# define JOIN "/join"
# define NICK "/nick"
# define LIST "/list"
# define CMD_COUNT 5
enum cmd_index {
	PM_I,
	CONN_I,
	JOIN_I,
	NICK_I,
	LIST_I,
};

typedef struct			s_cmdl
{
	char 				*cmd_name;
	void				(*fct_cmd)();
}						t_cmdl;

const t_cmdl			g_cmd_tab[CMD_COUNT + 1];

typedef struct			s_circ
{
	char 				*buf;
	int 				write_i;
	int					read_i;
	int					to_write;
	int 				data;
}						t_circ;

typedef struct			s_fd
{
	int					type;
	void				(*fct_read)();
	void				(*fct_write)();
	struct s_circ		circ;
	char				nick[9];
	struct s_channel	*channel;
}						t_fd;

int						usage(char *prog_name,char *error);
/*
**						shared/utils.c
*/
int 					max(int a, int b);
int 					min(int a, int b);
int						add_EOL(t_circ *circ);
int						check_EOL(t_circ *circ);
void					clear_circ(t_circ *circ);
int 					inci(int *i);
/*
**						shared/circ_mgt.c
*/
int						print_buf(t_circ *circ);
int						send_buf(t_circ *circ, int sock);
int						recv_buf(t_circ *circ, int s);
int						copy_to_buf(t_circ *circ, char *line);
/*
**						shared/clean_fd.c
*/
void					clean_fd(t_fd *fd);
/*
**						shared/protocol_mgt.c
*/
void					go_next_char(t_circ *circ);
void					trim_cmd_copy(t_circ *circ, char *copy, int len);
void					add_cmd(t_circ *circ, char *cmd, char prefix);
char					*return_cmd(t_circ *circ);
int						cmp_cmd(t_circ *circ, char *cmd);

void		print_buf_debug(t_circ *circ);
void		print_circ_info(t_circ *circ);
#endif

