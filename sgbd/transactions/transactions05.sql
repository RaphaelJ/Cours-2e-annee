T1:
SQL> SET TRANSACTION READ ONLY;

Transaction set.

SQL> SELECT nom FROM PAYS  WHERE CODEPAYS = 'ARB';

NOM
------------------------------------------------------------------------------------------
Suisse

T2:
SQL> UPDATE PAYS SET nom = 'Suisse' WHERE CODEPAYS = 'ARB';

1 row updated.

SQL> commit;

T1:
SQL> SELECT nom FROM PAYS  WHERE CODEPAYS = 'ARB';

NOM
------------------------------------------------------------------------------------------
Suisse

