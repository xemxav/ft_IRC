//
// Created by Xavier-Emmanuel Moreau on 30/04/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/serveur.h"

void 		delete_channel(t_env *e, t_channel *channel)
{
	t_channel 	*tmp;

	tmp = e->channels;
	while (tmp->next && tmp->next != channel)
		tmp = tmp->next;
	if (!tmp->next)
		fprintf(stderr, "%s Could not delete channel %s\n", ERR_LOG, channel->name);
	else
	{
		tmp->next = channel->next;
		free(channel->name);
		free(channel);
	}
}

t_channel 			*leave_channel(t_env *e, t_channel *current)
{
	current->p--;
	if (current != e->channels)
		delete_channel(e, current);
	return (e->channels);
}

t_channel		*join_channel(t_env *e, t_channel *current, char *c_name)
{
	t_channel *tmp;

	tmp = e->channels;
	leave_channel(e, current);
	while (tmp && ft_strncmp(tmp->name, c_name, 200) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (new_channel(e, c_name));
	tmp->p++;
	return (tmp);
}

t_channel		*free_channels(t_channel *head)
{
	t_channel	*tmp;

	if (!head)
		return (NULL);
	tmp = head->next;
	free(head->name);
	free(head);
	return (free_channels(tmp));
}

t_channel		*new_channel(t_env *e, char *name)
{
	t_channel *new;
	t_channel *tmp;

	if ((new = (t_channel*)malloc(sizeof(t_channel))) == NULL)
		error(e, "Channel Creation");
	new->name = ft_strdup(name);
	new->p = 0;
	new->next = NULL;
	if (!e->channels)
		e->channels = new;
	else
	{
		new->p = 1;
		tmp = e->channels;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}