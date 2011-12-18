SQL> SELECT NOM, '(' || TO_CHAR(DATENAIS, 'DD/MM/YYYY') || ')' DATE_DE_NAISSANCE,
  2  COALESCE(NUMDEP, 'Non specifie')
  3  FROM EMPLOYES
  4  WHERE NOM LIKE '_________'
  5   AND FLOOR((CURRENT_DATE - DATENAIS) / 365.25) > 50;

NOM                                                                             
--------------------------------------------------------------------------------
DATE_DE_NAISSANCE                    COALESCE(NUMDEP,'NONSPECIFIE')             
------------------------------------ ------------------------------------       
LHERMITTE                                                                       
(12/12/1955)                         Non specifie                               
                                                                                

SQL> SPOOL OFF;
