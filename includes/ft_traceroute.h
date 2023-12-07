/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxence <maxence@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:07:26 by matheme           #+#    #+#             */
/*   Updated: 2022/03/13 21:36:25 by maxence          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

// stdio.h allow the use of printf
# include <stdio.h>

// use for the define EXIT_FAILURE EXIT_SUCCESS
# include <stdlib.h>

// netdb.h allow the use of getaddrinfo and his define
# include <netdb.h>

// allow the use of setsocket
# include <sys/socket.h>
# include <sys/un.h>

// use to add getpid()
# include <unistd.h>

// arpa/inet.h allow to use of inet_ntop
# include <arpa/inet.h>

// use to add the struct icmp
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <netinet/in_systm.h>

// allow the use of gettimeoftheday
#include <sys/time.h>

// error.r add multiple define use for error
# include "error.h"

# include <string.h>
//allow to use of bzero

// allow the use of signal
#include <signal.h>

// allow the use of sqrt
#include <math.h>


# define IP_HDR_SIZE			20 // size of the ip header
# define ICMP_HDR_SIZE			ICMP_MINLEN // size of the header of the ICMP request
# define ICMP_PAYLOAD_SIZE		56 // size of the data of the ICMP request
# define PACKET_SIZE			(IP_HDR_SIZE + ICMP_HDR_SIZE + ICMP_PAYLOAD_SIZE) // Global packet size

# define LIST_OPTION "hmqfwn"
# define LIST_COMPLEXE_OPTION "mqfw"

typedef int option[128];

extern 	option			opt;

void			ft_bzero(void *ptr, int size);
void			*ft_memset(void *b, int c, size_t len);
int				ft_atoi(const char *str);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);

// initialise and get the raw_socket
int             raw_socket();

// dnslookup
int             lookup_host(const char *host, struct sockaddr **sockaddr);

// reverse dnsloolup
int				reverse_lookup_host (const char *ip, char *host, int host_size);


// send packet
int  send_packet(const int sockfd, struct sockaddr *dest, int seq, const char *domainname, struct timeval *sendtime, int iter);

// receive packet
char *receive_packet(const int sockfd, struct sockaddr *destaddr, int seq, struct timeval sendtime, int iter);

// error
int             error(int err, char *prog_name, char *host_name);
void			usage(char c);


char			**get_option(int ac, char **av, option opt);

//recupere le temps actuel
suseconds_t		get_time(void);

# endif