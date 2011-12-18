/*-----------------------------------------------------------------------------
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Vanstapel Herman EPL

 physlib\physlib.h
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 ----------------------------------------------------------------------------*/

#ifndef PHYSLIB
#define PHYSLIB
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include "../tcplib/tcplib.h"
#include <errno.h>

struct Physique
{
 struct sockaddr_in ai ; /* adresse du client */
 struct ip4 ip4cl,ip4se ;
 struct sockaddr_in sain ;       /* adresse du serveur */
 struct sockaddr_in oain ;	 /* origine du client */
 int desc  ;
 char Type ;
};

extern int errno ;

int CreerConnexion(struct Physique *pL,char * NCli,int pcli,char *NSer,int pser) ;
int FermetureConnexion(struct Physique *pL  ) ;
int VersCouchePhysique(struct Physique *pL,void *message,int tm ) ;
int OrigineCouchePhysique(struct Physique *pL, void *message,int *tm ) ;
int Repondre(struct Physique *pL,void *message,int tm ) ;
int IPDistante(struct Physique *pL) ;
int PortDistant(struct Physique *pL) ;
#endif
