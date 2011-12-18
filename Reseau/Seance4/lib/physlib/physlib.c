/*-----------------------------------------------------------------------------
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Vanstapel Herman EPL

 \physlib\physlib.c
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 ----------------------------------------------------------------------------*/
#include "physlib.h"
#include "../tcplib/tcplib.h"

int CreerConnexion(struct Physique *pL ,char * NCli,int pcli,char *NSer,int pser )
{
 int res ;
 int desc ;
 char *message ;
 struct hostent *phcli,*phser ;

 phcli = gethostbyname(NCli) ;
 if ( phcli == NULL )
    {
     perror("Nom client\n");
     return (-1) ;
    }
 memcpy(&(pL->ip4cl), phcli->h_addr_list[0],sizeof(pL->ip4cl)) ;
 fprintf(stderr,"IP du client:") ;
 afficher_adresse((struct ip4* )&(pL->ip4cl) ) ;

 /*----- adresse IP du serveur ---*/
 if (NSer != NULL )
 {
  phser = gethostbyname(NSer) ;
  if ( phser == NULL )
     {
      perror("Nom Serveur\n");
      return(-1) ;
     }
  memcpy(&(pL->ip4se), phser->h_addr_list[0],sizeof(pL->ip4se)) ;
  fprintf(stderr,"IP du serveur:") ;
  afficher_adresse((struct ip4* )&(pL->ip4se) ) ;
  pL->Type = 'C' ;
 }
 else
    pL->Type = 'S' ;

 if ((desc=creer_socket(SOCK_DGRAM,(u_long *)&(pL->ip4cl) ,pcli,&(pL->ai)))==-1)
    return(desc) ;

 pL->desc = desc ;
 if (NSer != NULL )
 {
  pL-> sain.sin_family = AF_INET ;
  memcpy( &(pL->sain.sin_addr.s_addr),&(pL->ip4se),4) ;
  pL-> sain.sin_port = htons(pser) ;
 }
 return(desc) ;
}

int FermetureConnexion(struct Physique *pL  )
{
 close( pL->desc ) ;
}


/* struct sockaddr_in sain ; */

int VersCouchePhysique(struct Physique *pL,void *message,int tm )
{
 if (pL->Type=='C')
  return(sendto(pL->desc,message,tm,0,(struct sockaddr *) &(pL->sain),sizeof(struct sockaddr_in))) ; else
 {
  fprintf(stderr,"Operation non autorisee pour un Serveur\n") ;
  return(-1) ;
 }
}

int Repondre(struct Physique *pL,void *message,int tm )
{
 return(sendto(pL->desc,message,tm,0,(struct sockaddr *) &(pL->oain),sizeof(struct sockaddr_in))) ;
}

int OrigineCouchePhysique(struct Physique *pL, void *message,int *tm )
{
 unsigned int ta ;
 ta = sizeof(struct sockaddr_in) ;
 return(recvfrom(pL->desc,message,*tm,0,(struct sockaddr *) &(pL->oain),&ta)) ;
}

int IPDistante(struct Physique *pL)
{
 struct sockaddr_in *pin ;
 int ip ;
 pin = &(pL->oain) ;
 ip = ntohl(pin->sin_addr.s_addr) ;
 return(ip)  ;
/*pin->sin_family      = AF_INET ;
  pin->sin_addr.s_addr = *ai  ;
  pin->sin_port        = htons(port) ; */
}

int PortDistant(struct Physique *pL)
{
 struct sockaddr_in *pin ;
 int port ;
 pin = &(pL->oain) ;
 port = ntohs(pin->sin_port) ;
 return(port)  ;
}



