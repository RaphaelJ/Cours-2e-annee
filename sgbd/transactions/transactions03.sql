T1:
SQL> SELECT nom FROM PAYS  WHERE CODEPAYS = 'ARB';

NOM
------------------------------------------------------------------------------------------
Arabie Saoudite


T2:
UPDATE PAYS SET nom = 'Suisse' WHERE CODEPAYS = 'ARB';
COMMIT;

T1:
SQL> SELECT nom FROM PAYS  WHERE CODEPAYS = 'ARB';

NOM
------------------------------------------------------------------------------------------
Suisse

