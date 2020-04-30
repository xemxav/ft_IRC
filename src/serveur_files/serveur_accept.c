
#include "../../includes/ft_irc.h"

void					serveur_accept(t_env *e, int s)
{
  int					cs;
  struct sockaddr_in	csin;
  socklen_t				csin_len;

  csin_len = sizeof(csin);
  if ((cs = accept(s, (struct sockaddr*)&csin, &csin_len)) == ERROR)
  		 error(e,"Error on accept");
  printf("New client #%d from %s:%d\n", cs,
	 inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
  clean_fd(&e->fds[cs]);
  e->fds[cs].type = FD_CLIENT;
  e->fds[cs].fct_read = client_read;
  e->fds[cs].fct_write = client_write;
}
