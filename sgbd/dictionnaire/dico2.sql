SQL> SELECT INITCAP(username), TO_CHAR(CREATED, 'HH:MI DD/MM/YYYY'),
  2         DEFAULT_TABLESPACE, EXPIRY_DATE
  3  FROM USER_USERS;

INITCAP(USERNAME)                                                               
--------------------------------------------------------------------------------
TO_CHAR(CREATED,'HH:MIDD/MM/YYYY')                                              
------------------------------------------------                                
DEFAULT_TABLESPACE                                                              
--------------------------------------------------------------------------------
EXPIRY_D                                                                        
--------                                                                        
Javauxra                                                                        
04:41 14/09/2010                                                                
USERS                                                                           
16/03/11                                                                        
                                                                                

SQL> SPOOL OFF;
