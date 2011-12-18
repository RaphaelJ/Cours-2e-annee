SQL> SELECT *
  2  FROM (SELECT *
  3        FROM ALL_OBJECTS
  4        WHERE OBJECT_NAME LIKE 'USER\_%' ESCAPE '\'
	  	 AND OBJECT_TYPE = 'VIEW'
  5	   ORDER BY OBJECT_NAME)
  5  WHERE ROWNUM <= 5;

OWNER                                                                           
--------------------------------------------------------------------------------
TABLE_NAME                                                                      
--------------------------------------------------------------------------------
TABLE_TYPE                                                                      
---------------------------------                                               
SYS                                                                             
USER_ADDM_FDG_BREAKDOWN                                                         
VIEW                                                                            
                                                                                
SYS                                                                             
USER_ADDM_FINDINGS                                                              
VIEW                                                                            

OWNER                                                                           
--------------------------------------------------------------------------------
TABLE_NAME                                                                      
--------------------------------------------------------------------------------
TABLE_TYPE                                                                      
---------------------------------                                               
                                                                                
SYS                                                                             
USER_ADDM_INSTANCES                                                             
VIEW                                                                            
                                                                                
SYS                                                                             
USER_ADDM_TASKS                                                                 

OWNER                                                                           
--------------------------------------------------------------------------------
TABLE_NAME                                                                      
--------------------------------------------------------------------------------
TABLE_TYPE                                                                      
---------------------------------                                               
VIEW                                                                            
                                                                                
SYS                                                                             
USER_ADDM_TASK_DIRECTIVES                                                       
VIEW                                                                            
                                                                                

SQL> SPOOL OFF;
