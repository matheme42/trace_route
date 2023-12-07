/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxence <maxence@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 12:08:48 by maxence           #+#    #+#             */
/*   Updated: 2022/03/13 21:37:18 by maxence          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "ft_traceroute.h"

suseconds_t	get_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
	{
		dprintf(1, "failed getting time of day\n");
		return (0);
	}
	return (curr_time.tv_sec * 1000000 + curr_time.tv_usec);
}

//   - calculates Round Trip Time in ms

static suseconds_t	get_rtt(struct timeval *send_time)
{
	return (get_time() - send_time->tv_sec * 1000000 - send_time->tv_usec);
}

static char *read_packet(char *packet, struct in_addr from, int recvd_seq, struct timeval sendtime, int iter)
{

 	char				*sender;
 	suseconds_t			rtt;
	char				host[256];
	static unsigned int	old_sender;

	if (iter == opt['q'] - 1)
		old_sender = 0;
	sender = inet_ntoa(from);
    rtt = get_rtt(&sendtime);
	ft_bzero(host, 256);
	reverse_lookup_host(sender, host, 256);
	if (old_sender != from.s_addr)
		opt['n'] ? dprintf(1, "%s ", sender) : dprintf(1, "%s (%s) ", host, sender);
	dprintf(1, "%ld.%02ld ms ", rtt / 1000l, rtt % 1000l);
	iter == 0 ? dprintf(1, "\n") : 0;
	old_sender = from.s_addr;
	return (sender);
}

char *receive_packet(const int sockfd, struct sockaddr *destaddr, int seq, struct timeval sendtime, int iter)
{
	char				packet[PACKET_SIZE];
	struct iphdr			*ipheader;
	socklen_t			len;
	struct sockaddr		from;

	if (iter == opt['q'] - 1)
		dprintf(1, "%2hd  ", seq);

    	ipheader = (struct iphdr*)packet;
	if (recvfrom(sockfd, packet, PACKET_SIZE, 0, &from, &len) >= 0)
		return (read_packet(packet, (struct in_addr){.s_addr = ipheader->saddr}, seq, sendtime, iter));
	iter == 0 ? dprintf(1, "* \n") : dprintf(1, "* ");
	return (NULL);
}
