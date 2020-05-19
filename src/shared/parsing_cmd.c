//
// Created by Xavier-Emmanuel Moreau on 12/05/2020.
//

#include "../../includes/ft_irc.h"

int 		dont_stop(char *buf, int i)
{
	int next;

	if (buf[i] == ' ' || buf[i] == 0)
		return (FALSE);
	next = (i == CBS - 1) ? 0 : i + 1;
	if (buf[i] == EOL[0] && buf[next] == EOL[1])
		return (FALSE);
	return (TRUE);
}

void		go_next_char(t_circ *circ)
{
	int in_space;

	in_space = 0;
	if (circ->buf[circ->read_i] != ' ')
		return;
	while (circ->read_i != circ->write_i)
	{
		if (circ->buf[circ->read_i] == ' ')
			in_space = 1;
		if (in_space && circ->buf[circ->read_i] != ' ')
			break ;
		inci(&circ->read_i);
		circ->data--;
	}
	if (circ->buf[circ->read_i] == EOL[0] &&
	circ->buf[circ->read_i + 1] == EOL[1])
	{
		circ->data = 0;
		circ->read_i = circ->write_i;
		circ->to_write = 0;
	}

}

void		trim_cmd_copy(t_circ *circ, char *copy, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		copy[i] = circ->buf[circ->read_i];
		circ->data--;
		i++;
		inci(&circ->read_i);
	}
	go_next_char(circ);
}


char 		*return_cmd(t_circ *circ)
{
	char	*cmd;
	size_t 	len;
	int 	p;

	len = 0;
	p = circ->read_i;
	while (dont_stop(circ->buf, p))
	{
		len++;
		inci(&p);
	}
	if ((cmd = ft_strnew(len + 1)) == NULL)
		return (NULL);
	cmd[len] = '\0';
	trim_cmd_copy(circ, cmd, len);
	return (cmd);
}

void		add_cmd(t_circ *circ, char *cmd, char prefix)
{
	int i;

	i = 0;
	if (prefix)
	{
		circ->buf[circ->write_i] = prefix;
		inci(&circ->write_i);
		circ->data++;
	}
	while (cmd[i] != '\0')
	{
		circ->buf[circ->write_i] = cmd[i];
		circ->data++;
		i++;
		inci(&circ->write_i);
	}
	circ->buf[circ->write_i] = ' ';
	inci(&circ->write_i);
	circ->data++;
}

int		cmp_cmd(t_circ *circ, char *cmd)
{
	int		start;
	int		i;

	start = circ->read_i;
	i = 0;
	while (cmd[i])
	{

		if (circ->buf[start] != cmd[i])
			return (FALSE);
		inci(&start);
		i++;

	}
	if (circ->buf[start] == ' ')
		return (TRUE);
	return (FALSE);
}