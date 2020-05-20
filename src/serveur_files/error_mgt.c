/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_mgt.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xem <xem@student.le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/05/20 15:37:21 by xem          #+#   ##    ##    #+#       */
/*   Updated: 2020/05/20 15:37:22 by xem         ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void		free_fds(t_env *e)
{
	int		i;

	i = 0;
	while (i <= e->max_fd)
	{
		if (e->fds[i].circ.buf != NULL)
			free(e->fds[i].circ.buf);
		i++;
	}
	free(e->fds);
}

void		clean_server(t_env *e)
{
	if (e->fds != NULL)
		free_fds(e);
	if (e->channels != NULL)
		free_channels(e->channels);
}

void		serveur_error(t_env *e, char *error)
{
	clean_server(e);
	fprintf(stderr, "%s %s\n", ERR_LOG, error);
	exit(EXIT_FAILURE);
}