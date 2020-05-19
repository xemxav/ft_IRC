//
// Created by Xavier-Emmanuel Moreau on 05/05/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"


void		clean_screen(void)
{
	printf("\033[2J\033[1;1H");

}

void		clean_input(void)
{
	ft_putstr("\033[2K");
	ft_putstr("\033[G");
}

void		print_prompt(t_envc *e)
{
	ft_putstr("\033[0;32m(");
	ft_putstr(e->channel);
	ft_putstr(") >>>\033[0m ");
}

void			client_record(t_envc *e)
{
	char	*line;
	t_circ	*circ;
	int		ret;

	circ = &e->circ;
	line = NULL;
	ret = get_next_line(0, &line);
	if (ret != -1)
	{
		if (ft_strlen(line) == 0)
		{
			if (line)
				free(line);
			return;
		}
		if (copy_to_buf(circ, line) != ft_strlen(line))
			client_error(e, "Error while recording user input");
		if (line)
			free(line);
		return;
	}
	client_error(e, "Error while recording user input");
}

