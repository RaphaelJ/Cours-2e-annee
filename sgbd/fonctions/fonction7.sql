SQL> SELECT e.NOM, c.NOM
  2  FROM EMPLOYES e
  3  INNER JOIN EMPLOYES c
  4      ON c.NUMSECU = COALESCE(e.NUMCHEF, e.NUMSECU)
  5  ORDER BY e.NUMCHEF ASC
  6  ;

NOM                                                                             
--------------------------------------------------------------------------------
NOM                                                                             
--------------------------------------------------------------------------------
HOFFMAN                                                                         
STALLONE                                                                        
                                                                                
DE NIRO                                                                         
CURTIS                                                                          
                                                                                
BEART                                                                           
CURTIS                                                                          
                                                                                

NOM                                                                             
--------------------------------------------------------------------------------
NOM                                                                             
--------------------------------------------------------------------------------
MOORE                                                                           
HOFFMAN                                                                         
                                                                                
CURTIS                                                                          
LHERMITTE                                                                       
                                                                                
LAFONT                                                                          
LHERMITTE                                                                       
                                                                                

NOM                                                                             
--------------------------------------------------------------------------------
NOM                                                                             
--------------------------------------------------------------------------------
REDFORD                                                                         
LHERMITTE                                                                       
                                                                                
STALLONE                                                                        
LHERMITTE                                                                       
                                                                                
CLAVIER                                                                         
BEART                                                                           
                                                                                

NOM                                                                             
--------------------------------------------------------------------------------
NOM                                                                             
--------------------------------------------------------------------------------
BERTHIER                                                                        
LAFONT                                                                          
                                                                                
BOHRINGER                                                                       
LAFONT                                                                          
                                                                                
CELARIE                                                                         
REDFORD                                                                         
                                                                                

12 rows selected.

SQL> SPOOL OFF;
