/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:40:36 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:49:46 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_FT_IRC_H
# define FT_IRC_FT_IRC_H
# include "../libft/includes/libft.h"
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/time.h>
# include <netdb.h>
# include <sys/time.h>
# include <sys/resource.h>

# define EOL "\r\n"
# define EOL_SIZE 2
# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2
# define NICK_SIZE  9
# define S_NAME "ft_irc"
# define PREFIX ':'
# define MAX_CHAN 5
# define PM "/msg"
# define CONNECT "/connect"
# define JOIN "/join"
# define LEAVE "/leave"
# define LIST "/list"
# define WRITE "/write"
# define NICK "/nick"
# define WHO "/who"
# define CMD_COUNT 8
# define PRIVATE ":private"
# define CBS	4096
# define DEFAULT_CHANNEL "#Public_Chatroom"
# define ERR_LOG "\033[0;31m[x]\033[0m"
# define PLUS_LOG "\033[0;32m[+]\033[0m"
# define MINUS_LOG "\033[0;33m[-]\033[0m"

typedef struct			s_circ
{
	char				*buf;
	int					write_i;
	int					read_i;
	int					to_write;
	size_t				data;
}						t_circ;

typedef struct			s_fd
{
	int					type;
	void				(*fct_read)();
	void				(*fct_write)();
	struct s_circ		circ;
	char				nick[9];
	struct s_channel	*write_chan;
	struct s_channel	*chan_bag[MAX_CHAN];
}						t_fd;

int						usage(char *prog_name, char *error);
/*
**						shared/utils.c
*/
int						max(int a, int b);
int						min(int a, int b);
size_t					add_eol(t_circ *circ);
int						check_eol(t_circ *circ);
/*
**						shared/index_mgt.c
*/
void					clear_circ(t_circ *circ);
int						inci(int *i);
int						dont_stop(char *buf, int i);
/*
**						shared/circ_mgt.c
*/
int						print_buf(t_circ *circ);
int						send_buf(t_circ *circ, int sock);
size_t					copy_to_buf(t_circ *circ, char *line);
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
#endif
