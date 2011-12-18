/*-----------------------------------------------------------------------------
 ============================================================================
  Vanstapel Herman EPL


 Fonctions de base TCP/IP
 ============================================================================
 ---------------------------------------------------------------------------- */
#include "tcplib.h"

int 	Ipv4ToInt(char *strsource,int *ip)
{
 char   dt[4] ;
 int	Membre[4] ;
 int	NumeroMembre,NombreDigits ;
 int	i,s,lg ;
 char   str[16] ; /* pour ne pas alterer l'original */
 i = 0 ;
 s = 0 ;
 NumeroMembre = 0 ;
 NombreDigits = 0 ;
 memset(Membre,0,sizeof Membre ) ;
 lg = strlen(strsource) ;
 strncpy(str,strsource,16) ;
 while (i<=lg)  /* Il faut traiter aussi le 0 de fin de chaine */
 {
  if (isdigit(str[i]))
    NombreDigits++ ;
  else
  if (str[i]=='.' || str[i]==0 )
  {
   char tmp[4] ;
   if (NombreDigits==0 || NombreDigits > 3 )
      return -1 ;
   if (NumeroMembre>3)
      return -1 ;
   str[i] = 0 ;
   strcpy(tmp,&str[s]) ;
   Membre[NumeroMembre] = atoi(tmp) ;
   s = i+1 ;
   NumeroMembre++ ;
   NombreDigits = 0 ;
  }
  else /* Pas un chiffre ni un point, ni un z�o */
     return -1 ;
  i++ ;
 }
 *ip = ( Membre[0] << 24 ) + ( Membre[1] << 16 ) + ( Membre[2] << 8 ) + Membre[3];
 return 1 ;   
}   

void Ipv4ToS(int ip,char *str)
{
  int NM[4] ;
  if (ip==0)
      strcpy(str,"0.0.0.0") ;
  else
     {
      NM[0] = ( ip >> 24 ) & 255 ;
      NM[1] = ( ip >> 16 ) & 255 ;
      NM[2] = ( ip >> 8 ) & 255 ;
      NM[3] = ip & 255 ;
      sprintf(str,"%d.%d.%d.%d",NM[0],NM[1],NM[2],NM[3]) ;
     }  
}

int generer_masque(int NbrBits )
{
 int Res ;
 int Decalage ;
 if ( NbrBits == 0   )
 	return( 0);
 Decalage = 32 - NbrBits ;
 Res = 1  ;
 while(NbrBits > 0 )
 {
   Res = Res << 1 ;
   Res = Res | 1 ;
   NbrBits -- ;
 }
 Res = Res << Decalage ;
 return (Res ) ;
}

void afficher_adresse( struct ip4 *adresse ) 
{
 fprintf(stderr,"%u.", adresse->b1) ;
 fprintf(stderr,"%u.", adresse->b2) ;
 fprintf(stderr,"%u.", adresse->b3) ;
 fprintf(stderr,"%u\n", adresse->b4) ;
}

int creer_socket(int type,u_long *ai, u_short port,struct sockaddr_in *pin) 
{
  struct ip4 uneip4 ;
  struct sockaddr_in sa ;

  int desc ; /* descripteur de la socket */
  int longueur = sizeof(struct sockaddr_in ) ; /* taille de l'adresse */
  struct hostent *phent ;
  u_long lg ;

 
  /*--- Creation de la socket ---------------------------*/
  if ((desc = socket(AF_INET, type, 0)) == -1 ){
	perror("Creation de socket impossible");
	return -1 ; }
  /*--- Preparation de l'adresse d'attachement -------- */
 
  memset(pin,0,sizeof( struct sockaddr_in )) ;
  pin->sin_family      = AF_INET ;
  pin->sin_addr.s_addr = *ai  ; 
  pin->sin_port        = htons(port) ; 
/*  sa.sin_family      = AF_INET ;
    sa.sin_addr.s_addr = *ai  ; 
    sa.sin_port        = htons(port) ; */
/* numero de port en format reseau */
  
  fprintf(stderr,"port %d \n",port) ;
  /*--- Demande d'attachement de la socket ------------*/
  if (bind(desc,(struct sockaddr *) pin,sizeof(struct sockaddr_in)) == -1) {
	perror("Attachement de la socket impossible") ;
	close(desc) ;
	return -1 ; }
  return desc ;
}
