SQL> SELECT INITCAP(NOM) NOM,
  2  CASE
  3      WHEN BAREME  < 55000 THEN '< 55 000'
  4      WHEN BAREME <= 94999 THEN '55 000 ~ 94999'
  5      WHEN BAREME >= 95000 THEN '>= 95 000'
         ELSE 'Inconnu'
  6  END SALAIRE
  7  FROM EMPLOYES
  8  WHERE UPPER(NOM) LIKE '%O%E';

NOM                                                                             
--------------------------------------------------------------------------------
SALAIRE                                                                         
------------------------------------------                                      
Stallone                                                                        
>= 95 000                                                                       
                                                                                
Moore                                                                           
< 55 000                                                                        
                                                                                
Monroe                                                                          
>= 95 000                                                                       
                                                                                

SQL> SPOOL OFF;
