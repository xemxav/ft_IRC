//
// Created by Xavier-Emmanuel Moreau on 27/04/2020.
//

#include "../../includes/ft_irc.h"

static int create_serveur(t_env *env)
{
	int yes;

	yes = 1;
	if ((env->sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		usage(env->args[0], "Could not create socket");
	if (setsockopt(env->sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		usage(env->args[0], "Could not create option");
	if (bind(env->sock,(struct sockaddr *)&(env->host_addr),
			sizeof(struct sockaddr)) == ERROR)
		usage(env->args[0], "Failed to bind socket");
	if (listen(env->sock, 5) == ERROR)
		usage(env->args[0], "Failed to listen on port");
	printf("[+] Listening on port %s\n", env->args[1]);
	return (TRUE);
}

static void	create_host_adr(t_env *env)
{
	unsigned int port;


	env->host_addr.sin_port = htons(port);
	env->host_addr.sin_family = AF_INET;
	env->host_addr.sin_addr.s_addr= INADDR_ANY;
}

void create_env_serveur(t_env *env, char **av)
{
	ft_bzero(env, sizeof(env));
	env->args = av;
	create_host_adr(env);
    create_serveur(env);
}