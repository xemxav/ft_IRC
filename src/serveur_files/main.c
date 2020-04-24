//
// Created by Xavier-Emmanuel Moreau on 23/04/2020.
//

#include "../../includes/ft_irc.h"

int create_serveur(t_env *env)
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

void	create_host_adr(t_env *env)
{
	unsigned int port;

	if (!(port = ft_atoi(env->args[1])))
		usage(env->args[0], "Not a proper port");
	env->host_addr.sin_port = htons(port);
	env->host_addr.sin_family = AF_INET;
	env->host_addr.sin_addr.s_addr= INADDR_ANY;
}

int main(int ac, char**av)
{
	t_env				env;
	t_client			client;
	char				buffer[512];
	ssize_t				length_recv;
	socklen_t 			sin_size;

	if (ac < 2)
		usage(av[0], "<port>");
	ft_bzero(&env, sizeof(env));
	ft_bzero(&client, sizeof(client));
	env.args = av;
	create_host_adr(&env);
	create_serveur(&env);
	while (1)
	{
		sin_size = sizeof(struct sockaddr_in);
		client.sock = accept(env.sock, (struct sockaddr *)&(client.client_addr), &sin_size);
		length_recv = recv(client.sock, buffer, 512, 0);
		if (length_recv == 0)
			usage(env.args[0], "end receiving");
		else
		{
			buffer[length_recv] = '\0';
			printf("%s\n", buffer);
		}
	}
	return (0);
}