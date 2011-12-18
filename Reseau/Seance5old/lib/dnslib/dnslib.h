/*--------------------------------------------------------------------
 Vanstapel Herman EPL

 Service DNS
-----------------------------------------------------------------------
-----------------------------------------------------------------------

-----------------------------------------------------------------------
 C'est la couche liaison
------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "../evlib/evlib.h"
#include "../physlib/physlib.h"
#include "../protocol/protocol.h"

/* struct RequeteDNS{
      int Type ;
      int Numero ;
      int IP ;
      NomDNS Nom ;
}; */

struct NomsResolus
{
 NomDNS Nom  ;
 int	Ip   ;
 int    Vide ;
 int	Fin  ;
};


int AjoutCacheDNS(struct NomsResolus LesNomsResolus[],NomDNS Nom,int UneIp);
void AfficheCacheDNS(struct NomsResolus LesNomsResolus[] ) ;
int EffaceCacheDNS(struct NomsResolus  LesNomsResolus[]) ;
struct NomsResolus* InitialiseCacheDNS(int NE) ;
int RechercheNomCacheDNS(struct NomsResolus LesNomsResolus[],NomDNS NomAResoudre) ;
int RechercheNomDB(char* FichierDNS,char *NomAResoudre) ;


