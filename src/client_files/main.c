//
// Created by Xavier-Emmanuel Moreau on 23/04/2020.
//

#include "../../includes/ft_irc.h"
#include "../../includes/client.h"


void	host_from_av(t_envc *e, char **av)
{
	int		port;

	if ((port = ft_atoi(av[2])) == 0)
		usage(av[0], "<host> <port>");
	e->port = port;
	e->host = ft_strdup(av[1]);

}

void host_from_input(t_envc *e)
{
	char	*line;

	printf("Enter a hostname or an ip adress\n");
	print_prompt(e);
	if (get_next_line(1, &e->host) < 0)
		client_error(e, "Entering hostname");
	clean_input();
	printf("Enter a port number:\n");
	print_prompt(e);
	if (get_next_line(1, &line) < 0)
		client_error(e, "Entering port");
	if ((e->port = ft_atoi(line)) == 0)
	{
		free(line);
		client_error(e, "Not a good port number");
	}
	free(line);
}

void	run_session(t_envc *e)
{
	clean_screen();
	create_client(e);
	run_client(e);
}

int main(int ac, char**av, char **env)
{

	t_envc	e;

	if (ac != 3 && ac != 1)
		return (usage(av[0], "[<host>] [<port>]"));
	init_envc(&e, env);
	if (ac == 3)
		host_from_av(&e, av);
	else
		host_from_input(&e);
	run_session(&e);
	return (0);
}


