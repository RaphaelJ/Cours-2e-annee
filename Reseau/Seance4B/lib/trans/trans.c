#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[] )
{
 FILE *fr ;
 FILE *fw ;
 char ch  ;  

 if (argc != 3 )
    exit(0) ;

 printf("%s \n",argv[1] ) ;
 printf("%s \n",argv[2] ) ;

 fr = fopen(argv[1],"r") ;
 if ( fr == NULL )
    {
     perror("open r") ;
     exit(0) ;
    }
 fw = fopen(argv[2],"w") ;
 if ( fw == NULL )
    {
     perror("open w") ;
     exit(0) ;
    } 

 ch = fgetc(fr) ; 
 while(!feof(fr))
 {
  if ( ch == 13 ) 
     ;
  else
     fputc(ch,fw) ;
  ch = fgetc(fr) ;
 }
 fclose(fr) ;  
 fclose(fw) ;
}    
