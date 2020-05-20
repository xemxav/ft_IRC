//
// Created by Xavier-Emmanuel Moreau on 06/05/2020.
//

#include "../../includes/ft_irc.h"

int			send_buf(t_circ *circ, int sock)
{
	int		to_send;
	int		ret;


	if (circ->read_i == circ->write_i)
	{
		circ->to_write = 0;
		return (TRUE);
	}
	if (circ->read_i < circ->write_i)
		to_send = circ->write_i - circ->read_i;
	else
		to_send = CBS - circ->read_i;
	if ((ret = send(sock, circ->buf + circ->read_i, to_send, 0))== ERROR)
		return (ERROR);
	circ->read_i += ret;
	if (circ->read_i == CBS)
		circ->read_i = 0;
	circ->data -= ret;
	return (send_buf(circ, sock));
}

int			recv_buf(t_circ *circ, int s)
{
	int		r;

	r = recv(s, circ->buf + circ->write_i, CBS - circ->write_i, 0);
	if (r < 0)
		return (ERROR);
	if (r == 0)
		return (0);
	printf("Recu %d octet\n", r);
	circ->write_i += r;
	circ->to_write = check_EOL(circ);
	if (circ->to_write)
		return (circ->data);
	return (recv_buf(circ, s));
}

int			print_buf(t_circ *circ)
{
	int		to_print;
	int		printed;
	char	*s;

	if (circ->write_i == circ->read_i)
	{
		circ->to_write = FALSE;
		return (TRUE);
	}
	if (circ->read_i < circ->write_i)
		to_print = circ->write_i - circ->read_i;
	else
		to_print = CBS - circ->read_i;
	if ((s = ft_strsub(circ->buf, circ->read_i, to_print)) == NULL)
		return (ERROR);
	printed = printf("%s", s);
	free(s);
	circ->read_i += printed;
	if (circ->read_i == CBS)
		circ->read_i = 0;
	circ->data -= printed;
	return (print_buf(circ));
}

void		print_buf_debug(t_circ *circ)
{
	t_circ circc;

	printf("\033[0;33m");
	ft_memcpy(&circc, circ, sizeof(t_circ));
//	printf("info de debug:\n");
//	print_circ_info(&circc);
	print_buf(&circc);
//	printf("-- fin debug\n");
	printf("\033[0m");
}

void		print_circ_info(t_circ *circ)
{
	printf("circ est a %p\n", circ);
	printf("buf est a %p\n", circ->buf);
	printf("read_i = %d, write_i = %d, data = %d\n", circ->read_i, circ->write_i, circ->data);
	printf("to write = %d\n", circ->to_write);
}

int			copy_to_buf(t_circ *circ, char *line)
{
	ssize_t	buf_len;
	ssize_t	len;
	int		rec;

	if (*line == '\0')
		return (add_EOL(circ) - EOL_SIZE);
	buf_len = CBS - circ->write_i;
	len = ft_strlen(line);
	rec = min(len, buf_len);
	ft_strncpy(circ->buf + circ->write_i, line, rec);
	circ->data += rec;
	circ->write_i += rec;
	if (circ->write_i == CBS)
		circ->write_i = 0;
	return (copy_to_buf(circ, line + rec));
}