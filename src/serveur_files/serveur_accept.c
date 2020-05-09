
#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void 					send_first_instruction(e, circ)
{

}

void					serveur_accept(t_env *e, int s)
{
	int						cs;
	struct sockaddr_in		csin;
	socklen_t				csin_len;

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
  	if ((e->fds[cs].circ.buf = (char*)malloc(CIRC_BUFF_SIZE)) == NULL)
		error(e, "Client Buffer Creation");
  	e->fds[cs].channel = e->channels;
  	copy_to_buf(&e->fds[cs].circ, "Welcome to the serveur");
  	// ajouter dans le buffer le retout "vonnecter sur serveur, nick et channel
  	// passe le cs en FD read ?
}

