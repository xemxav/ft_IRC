//
// Created by Xavier-Emmanuel Moreau on 05/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

static int copy_to_buf(t_circ *circ, char *line)
{
	ssize_t buf_len;
	ssize_t len;
	int		rec;

	if (*line == '\0')
		return (add_EOL(circ));
	buf_len = CIRC_BUFF_SIZE - circ->write_i;
	len = ft_strlen(line);
	rec = min(len, buf_len);
	ft_strncpy(circ->buf + circ->write_i, line, rec);
	circ->data += rec;
	circ->write_i += rec;
	if (circ->write_i == CIRC_BUFF_SIZE)
		circ->write_i = 0;
	return (copy_to_buf(circ, line + rec));
}

int	client_send(t_envc *e)
{
	t_circ	*circ;
	int		to_send;
	int		ret;


	circ = &e->circ;
	if (circ->read_i == circ->write_i)
		return (TRUE);
	if (circ->read_i < circ->write_i)
		to_send = circ->write_i - circ->read_i;
	else
		to_send = CIRC_BUFF_SIZE - circ->read_i;
	ret = send(e->sock, circ->buf + circ->read_i, to_send, 0);
	circ->read_i += ret;
	if (circ->read_i == CIRC_BUFF_SIZE)
		circ->read_i = 0;
	circ->data -= ret;
	printf("ret = %d - read_i = %d - data = %d - write_i = %d\n", ret, circ->read_i, circ->data, circ->write_i);
	return (client_send(e));
}

int	client_record(t_envc *e)
{
	char	*line;
	t_circ	*circ;
	int ret;

	circ = &e->circ;
	line = NULL;
	ret = get_next_line(0, &line);
	if (ret != -1)
	{
		ret = TRUE;
		if (copy_to_buf(circ, line) != ft_strlen(line))
			ret = ERROR;
		free(line);
		return (ret);
	}
	return (ret);
}


