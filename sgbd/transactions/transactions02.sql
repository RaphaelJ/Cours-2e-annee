T1:
UPDATE PAYS SET nom = 'Arabie Saoudite' WHERE CODEPAYS = 'ARB';

1 row updated.

T2:
UPDATE PAYS SET nom = 'Arabie' WHERE CODEPAYS = 'ARB';

0 rows updated.

T1:
commit;

T2:
commit;

T1:
SELECT * FROM PAYS  WHERE CODEPAYS = 'ARB';

CODEPAYS  NOM
--------- ------------------------------------------------------------------------------------------
DEVISE
------------------------------------------------------------
ARB       Arabie Saoudite
petrol

