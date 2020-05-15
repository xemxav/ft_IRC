
#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"


void					serveur_accept(t_env *e, int s)
{
	int						cs;
	struct sockaddr_in		csin;
	socklen_t				csin_len;
	char					*sock;

	csin_len = sizeof(csin);
  	if ((cs = accept(s, (struct sockaddr*)&csin, &csin_len)) == ERROR)
  		 error(e,"Error on accept");
  	printf("%s New client #%d from %s:%d\n", PLUS_LOG, cs,
  			inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
  	clean_fd(&e->fds[cs]);
  	e->fds[cs].type = FD_CLIENT;
  	e->fds[cs].fct_read = client_read;
  	e->fds[cs].fct_write = client_write;
  	ft_bzero(&e->fds[cs].circ, sizeof(t_circ));
  	if ((e->fds[cs].circ.buf = (char*)malloc(CBS)) == NULL)
		error(e, "Client Buffer Creation");
  	e->fds[cs].channel = e->channels;
  	add_cmd(&e->fds[cs].circ, S_NAME, PREFIX);
  	if ((sock = ft_itoa(cs)) == NULL)
  		error(e, "Coudl not create client socket");
  	add_cmd(&e->fds[cs].circ, sock, 0);
  	free(sock);
  	copy_to_buf(&e->fds[cs].circ, "Welcome to the serveur, "
							 "you are connected on channel #Public_Chatroom");
//  	send_buf(&e->fds[cs].circ, cs);
}

