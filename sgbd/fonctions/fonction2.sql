SQL> SELECT FLOOR((CURRENT_DATE - TO_DATE('28/10/1955', 'DD/MM/YYYY')) / 365.25) || ' ans'
  2  FROM DUAL;

FLOOR((CURRENT_DATE -TO_DATE('28/10/1955','DD/MM/YYYY'))/365.25)||'ANS'                    
--------------------------------------------------------------------------------
54 ans                                    

SQL> SELECT MONTHS_BETWEEN(CURRENT_DATE, TO_DATE('28/10/1955', 'DD/MM/YYYY')) / 12 FROM DUAL;

MONTHS_BETWEEN(CURRENT_DATE,TO_DATE('28/10/1955','DD/MM/YYYY'))/12
------------------------------------------------------------------
                                                        54,9166667

SQL> SELECT EXTRACT (YEAR FROM CURRENT_DATE) - 1955 FROM DUAL;

EXTRACT(YEARFROMCURRENT_DATE)-1955
----------------------------------
                                55



SQL> SELECT (CURRENT_DATE - TO_DATE('28/10/1955', 'DD/MM/YYYY')) YEAR TO MONTH
  2  FROM DUAL;

Page :   1                     Liste des employes                 User: JAVAUXRA
(CURRENT_DATE-TO_DATE('28/10/1955','DD/MM/YYYY'))YEARTOMONTH
---------------------------------------------------------------------------
+54-11




