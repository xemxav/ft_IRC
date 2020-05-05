//
// Created by Xavier-Emmanuel Moreau on 04/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/ft_irc.h"


int		max(int a, int b)
{
	return ((a > b) ? a : b);
}

int		min(int a, int b)
{
	return ((a < b) ? a : b);
}

int 	add_EOL(t_circ *circ)
{
	int i;

	i = 0;
	while (i < EOL_SIZE)
	{
		if (circ->write_i == CIRC_BUFF_SIZE)
			circ->write_i = 0;
		circ->buf[circ->write_i] = EOL[i];
		circ->write_i++;
		i++;
	}
	circ->data += 2;
	return (circ->data);
}

int		check_EOL(t_circ *circ)
{
	int i;
	int check;
	int match;

	i = EOL_SIZE;
	match = 0;
	while (i > 0)
	{
		check = circ->write_i - i;
		if (check < 0)
			check = CIRC_BUFF_SIZE - check;
		if (circ->buf[check] == EOL[EOL_SIZE - i])
			match++;
		i--;
	}
	if (match == 2)
		return (TRUE);
	return (FALSE);
}

int		print_buf(t_circ *circ)
{
	int	to_print;
	int printed;
	char	*s;

	if (circ->write_i == circ->read_i)
	{
		circ->to_write = FALSE;
		return (TRUE);
	}
	if (circ->read_i < circ->write_i)
		to_print = circ->write_i - circ->read_i;
	else
		to_print = CIRC_BUFF_SIZE - circ->read_i;
	if ((s = ft_strsub(circ->buf, circ->read_i, to_print)) == NULL)
		return (ERROR);
	printed = printf("%s", s);
	free(s);
	circ->read_i += printed;
	if (circ->read_i == CIRC_BUFF_SIZE)
		circ->read_i = 0;
	circ->data -= printed;
	return (print_buf(circ));
}