T1:

SQL> SELECT * FROM B12 WHERE NR = 2 FOR UPDATE;

        NR ENSEIGNANT                        MONTANT
---------- ------------------------------ ----------
         2 Hello                                2000

SQL> SELECT * FROM B12 WHERE NR = 1 FOR UPDATE;
SELECT * FROM B12 WHERE NR = 1 FOR UPDATE
              *
ERROR at line 1:
ORA-00060: deadlock detected while waiting for resource


T2:
SQL> SELECT * FROM B12 WHERE NR = 1 FOR UPDATE;

        NR ENSEIGNANT                        MONTANT
---------- ------------------------------ ----------
         1 Thiry                                1000

SQL> SELECT * FROM B12 WHERE NR = 2 FOR UPDATE;


