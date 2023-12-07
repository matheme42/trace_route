/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxence <maxence@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:05:41 by maxence           #+#    #+#             */
/*   Updated: 2022/03/13 21:28:58 by maxence          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "ft_traceroute.h"

option	opt;

static void interrupt(int value)
{
	exit(EXIT_SUCCESS);
}

static int traceroute(const char *hostname, struct sockaddr *clientaddr)
{
	static int		seq = 0;
	struct timeval	sendtime;
	char			*dest;
	char			*rcv;
	int				iter;

	// creation de la socket personnalysé
	if (raw_socket() < 0) {
		return (raw_socket());
	}

	if (!(dest = malloc(40)))
		return (EXIT_FAILURE);
	dest = strcpy(dest, inet_ntoa(((struct sockaddr_in *)clientaddr)->sin_addr));
	seq = opt['f'] ? opt['f'] : seq;
	while (++seq && (!opt['m'] || seq <= opt['m'])) {
		iter = opt['q'];
		while (iter--) {
			if (!send_packet(raw_socket(), clientaddr, seq, hostname, &sendtime, iter))
				if ((rcv = receive_packet(raw_socket(), clientaddr, seq, sendtime, iter)))
					if (!ft_strcmp(dest, rcv) && iter == 0)
					 {
						free(dest);
						return (EXIT_SUCCESS);
					 }
		
		}
	}
}

int main(int ac, char **av)
{
	struct	sockaddr	*destaddr;
	char				*progname;
	int					err;

	//accept only if you give an argument
	if (ac < 2)
		return (error(E_USAGE, av[0], NULL));
	ft_bzero(opt, sizeof(option));
	progname = av[0];
	opt['q'] = 3;
	opt['f'] = 0;
	opt['m'] = 60;
	av = get_option(ac - 1, &av[1], opt);

	if (opt['h'] || !*av)
		usage(0);

	//transform the domain to an binary address
    if ((err = lookup_host(*av, &destaddr)))
		return (error(err, progname, *av));
	
	// catch the signal
	signal(SIGINT, interrupt);

	// start the traceroute
	if ((err = traceroute(*av, destaddr)))
		return (error(err, progname, *av));

	return (EXIT_SUCCESS);
}

