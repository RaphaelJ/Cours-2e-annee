#define MAX_PKT 512 
typedef enum { false,true } boolean ;
typedef unsigned int num_seq ;
typedef struct {
		unsigned char data[MAX_PKT] ;
	       } paquet ;

typedef enum{ data,ack,nak } type_trame ;
typedef struct {
	type_trame type ;
	num_seq	 seq ;
	num_seq  ack ;
	paquet  info ;
      } trame ;

#define inc(k) if(k<MAX_SEQ)k=k+1;else k=0;  
