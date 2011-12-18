SQL> SELECT INDEX_NAME, TABLE_NAME,
  2         CASE
  3           WHEN UNIQUENESS = 'UNIQUE' THEN 'oui'
  4           ELSE 'non'
  5         END
  6  FROM USER_INDEXES;

INDEX_NAME                                                                      
--------------------------------------------------------------------------------
TABLE_NAME                                                                      
--------------------------------------------------------------------------------
CASEWHENU                                                                       
---------                                                                       
CPPROJETS                                                                       
PROJETS                                                                         
oui                                                                             
                                                                                
CPEMPPRO                                                                        
EMPPRO                                                                          
oui                                                                             

INDEX_NAME                                                                      
--------------------------------------------------------------------------------
TABLE_NAME                                                                      
--------------------------------------------------------------------------------
CASEWHENU                                                                       
---------                                                                       
                                                                                
CPEMPLOYESNUMSECU                                                               
EMPLOYES                                                                        
oui                                                                             
                                                                                
CPEMPNO                                                                         
EMP                                                                             

INDEX_NAME                                                                      
--------------------------------------------------------------------------------
TABLE_NAME                                                                      
--------------------------------------------------------------------------------
CASEWHENU                                                                       
---------                                                                       
oui                                                                             
                                                                                
CPDEPT                                                                          
DEPT                                                                            
oui                                                                             
                                                                                
CPDEPARTEMENTS                                                                  

INDEX_NAME                                                                      
--------------------------------------------------------------------------------
TABLE_NAME                                                                      
--------------------------------------------------------------------------------
CASEWHENU                                                                       
---------                                                                       
DEPARTEMENTS                                                                    
oui                                                                             
                                                                                

6 rows selected.

SQL> SPOOL OFF;
