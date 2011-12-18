/*-----------------------------------------------------------------------------
 ============================================================================
  Vanstapel Herman EPL

 Fonctions de base TCP/IP
 ============================================================================
 ----------------------------------------------------------------------------*/
#ifndef TCPLIB
#define TCPLIB
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>

struct ip4 {
	u_char b1 ;
        u_char b2 ;
	u_char b3 ;
	u_char b4 ;
	};

int	Ipv4ToInt(char *s,int *ip) ;
void	Ipv4ToS(int ip, char *s) ; 
void    afficher_adresse( struct ip4 *adresse ) ;
int     creer_socket(int,u_long *ai, u_short port,struct sockaddr_in *pin) ;
int     generer_masque(int NbrBits ) ;
#endif 
