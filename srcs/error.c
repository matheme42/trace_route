/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxence <maxence@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 15:30:37 by maxence           #+#    #+#             */
/*   Updated: 2022/03/13 21:37:32 by maxence          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "ft_traceroute.h"

int error(int err, char *prog_name, char *host_name)
{

	switch (err)
	{
		case E_USAGE:
			usage(0);
		break ;
		case E_UNKNOWN_HOST:
			dprintf(2, "%s: unknown host\n", host_name);
			dprintf(2, "Cannot handle \"host\" cmdline arg '%s' on position 1 (argc 1)\n", host_name);
		break ;
		case E_SOCKET:
			perror(prog_name);
		break ;
		case E_SEND_SOCKET:
			dprintf(2, "cannot send the packet");
		break ;
	}
	return (EXIT_FAILURE);
}

void usage(char c)
{
	if (c)
		dprintf(1, "ft_traceroute: option invalide -- '%c'\n", c);
	dprintf(2, "Usage: ft_traceroute [-hn] [-m ttl_max 1 - 255] [-f ttl_min 1 - 255] [-w waittimes 1 - 60] [-q nQueries 1 - 10] host\n");
	exit(EXIT_FAILURE);
}