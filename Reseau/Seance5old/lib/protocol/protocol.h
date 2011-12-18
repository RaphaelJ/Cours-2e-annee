#ifndef PROTOCOL
#define PROTOCOL 1
#define TBUFFERTRANSPORT  512


static int Liaison ;

typedef enum { data,ack,nak } type_trame ;

enum TypeDNS { 
               TREQUETEDNS=1,
               TREPONSEDNS=2
	     } ;  

typedef char NomDNS[80]  ;

struct RequeteDNS{
enum TypeDNS Type ;
int Numero ;
int IP ;
NomDNS Nom ;
};

struct Segment
{
 int	PortSource;
 int	PortDestination;
 char   Buffer[TBUFFERTRANSPORT] ;
};

#define TBUFFERPAQUET  sizeof(struct Segment)

struct Paquet
{
 int  IPSource ;
 int  IPDestination ;
 int  Protocole ; /* le champ type */
 int  Numero ;
 char Buffer[TBUFFERPAQUET] ;
};

#define ICMP 1
#define IP  4
#define UDP 16
#define TCP 17
#define ICMPECHO   221
#define ICMPRESPONSE 222

#define TBUFFERTRAME  sizeof(struct Paquet)

struct mac 
{
 short int Constructeur ;
 int       Numero ;
} ;

struct Trame
{
 int  Numero ;
 type_trame type ;
 struct mac MacSource ;
 struct mac MacDestination ;
 int Flag ;
 int seq ;
 int  ack ;
 char Buffer[TBUFFERTRAME] ;
};

#define inc(k) if(k<MAX_SEQ)k=k+1;else k=0; 
#endif
