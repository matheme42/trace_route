/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dnslookup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxence <maxence@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:50:47 by maxence           #+#    #+#             */
/*   Updated: 2022/03/13 20:32:19 by maxence          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "ft_traceroute.h"

//                      localhost       0x 0a 0f 0t 0x ..   
int lookup_host (const char *host, struct sockaddr **sockaddr)
{
	struct	addrinfo hints;
	struct	addrinfo *res;
	void	*ptr;

	bzero(&hints, sizeof(hints));

	hints.ai_socktype = SOCK_DGRAM; // send UDP packet
	hints.ai_family = AF_INET; // return only IPV4 addr

	if (!getaddrinfo (host, NULL, &hints, &res))
	{
		*sockaddr = res->ai_addr;
		return (EXIT_SUCCESS);
	}
	return (E_UNKNOWN_HOST);
}

//                      localhost       0x 0a 0f 0t 0x ..   
int reverse_lookup_host (const char *ip, char *host, int host_size)
{
	struct	addrinfo hints;
	struct	addrinfo *res;
	void	*ptr;

	bzero(&hints, sizeof(hints));

	hints.ai_socktype = SOCK_DGRAM; // send UDP packet
	hints.ai_family = AF_INET; // return only IPV4 addr

	if (getaddrinfo (ip, NULL, &hints, &res))
		return (EXIT_FAILURE);
	getnameinfo(res->ai_addr, res->ai_addrlen, host, host_size, NULL, 0, 0);
	return (EXIT_SUCCESS);
}