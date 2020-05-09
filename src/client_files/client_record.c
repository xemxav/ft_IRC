//
// Created by Xavier-Emmanuel Moreau on 05/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"

//void					clean_input(void)
//{
//	char				tmp[CIRC_BUFF_SIZE];
//
//	ft_memset(tmp, 0, CIRC_BUFF_SIZE);
//	ft_memset(tmp, '\b', NICK_SIZE + 4);
//	ft_putstr(tmp);
//	ft_memset(tmp, 0, CIRC_BUFF_SIZE);
//	ft_memset(tmp, ' ', NICK_SIZE + 4);
//	ft_putstr(tmp);
//	ft_memset(tmp, 0, CIRC_BUFF_SIZE);
//	ft_memset(tmp, '\b', NICK_SIZE + 4);
//	ft_putstr(tmp);
//}

void					clean_input(t_envc *e)
{
//	char				tmp[4];
//

//	if (e->pr)
//	{
//		ft_memset(tmp, '\b', 4);
//		printf("%s", tmp);
//		e->pr = 0;
//	}
//	printf("\033[J");
	ft_putstr("\033[2K");
	ft_putstr("\033[G");
}

void	print_prompt(t_envc *e)
{
	ft_putstr("\033[0;32m>>>\033[0m ");
}

int		client_record(t_envc *e)
{
	char	*line;
	t_circ	*circ;
	int ret;

//	printf("rentre dans client record %d\n", e->etape++);
	circ = &e->circ;
	line = NULL;
	ret = get_next_line(0, &line);
	if (ret != -1)
	{
		ret = TRUE;
		if (ft_strlen(line) == 0)
			return (ret);
		if (copy_to_buf(circ, line) != ft_strlen(line))
			ret = ERROR;
		free(line);
		return (ret);
	}
	return (ret);
}


