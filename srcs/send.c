/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxence <maxence@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:11:02 by maxence           #+#    #+#             */
/*   Updated: 2022/03/13 20:48:19 by maxence          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "ft_traceroute.h"

// Calculating the Check Sum 
static unsigned short checksum(void *b, int len) 
{
    unsigned short  *buf = b;
    unsigned int    sum = 0;
    unsigned short  result;

    for ( sum = 0; len > 1; len -= 2 )
        sum += *buf++;
    if ( len == 1 )
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

static void sendfirst(int sendbyte, struct sockaddr *dest, const char *domainname)
{
    char *destip;

    destip = inet_ntoa(((struct sockaddr_in *)dest)->sin_addr);
    dprintf(1, "traceroute to %s (%s) %d hops max, %d byte packets\n", domainname , destip, opt['m'], ICMP_PAYLOAD_SIZE, PACKET_SIZE);
}

int  send_packet(const int sockfd, struct sockaddr *dest, int seq, const char *domainname, struct timeval *sendtime, int iter)
{
	char    packet[PACKET_SIZE];

    struct iphdr *ipheader = (struct iphdr*)packet;
    struct icmphdr *icmpheader = (struct icmphdr*)&packet[IP_HDR_SIZE];
  
    ft_bzero(ipheader, sizeof(*ipheader));
    ft_bzero(icmpheader, sizeof(*icmpheader));
    ft_bzero(packet, PACKET_SIZE);

    // IP HEADER
    ipheader->version = 4;
    ipheader->ihl = IP_HDR_SIZE / 4;
    ipheader->tos = 0;
    ipheader->tot_len = htons(PACKET_SIZE); // convert little endian to big endian
    ipheader->ttl = seq;
    ipheader->frag_off = htons(0);
    ipheader->protocol = IPPROTO_ICMP; // 1 for ICMP
    ipheader->saddr = INADDR_ANY;
    ipheader->daddr = (unsigned int)((struct sockaddr_in *)dest)->sin_addr.s_addr;
    ipheader->check = 0;

    // ICMP DATA
    ft_memset(icmpheader, 42, PACKET_SIZE - IP_HDR_SIZE); // fill with random data
    gettimeofday((void*)&packet[IP_HDR_SIZE + ICMP_HDR_SIZE + 4], NULL);


    // ICMP HEADER
    icmpheader->type = ICMP_ECHO;
    icmpheader->code = 0;
    icmpheader->un.echo.id = getpid();
    icmpheader->un.echo.sequence = htons(seq);
    icmpheader->checksum = 0;
    icmpheader->checksum = checksum(icmpheader, ICMP_PAYLOAD_SIZE + ICMP_HDR_SIZE);

    int sendbyte = sendto(sockfd, packet, PACKET_SIZE, 0, dest, sizeof(*dest));
    gettimeofday(sendtime, NULL);
    if (sendbyte < 0) {
        perror("ft_traceroute: sendto");
        return (1);
    }
    if (seq == 1 && iter == opt['q'] - 1)
        sendfirst(sendbyte, dest, domainname);

    return (0);
}
