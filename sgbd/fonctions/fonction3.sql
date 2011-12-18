SQL> SELECT e.NOM,
  2         CASE WHEN e.NUMCHEF IS NULL
  3                   THEN '*******'
  4              ELSE RPAD(e.BAREME, 7, '*')
  5         END BAREME
  6  FROM EMPLOYES e
  7  LEFT JOIN EMPLOYES c
  8       ON c.NUMSECU = e.NUMSECU;


Page :   1                     Liste des employes                 User: JAVAUXRA

NOM
--------------------------------------------------------------------------------
RPAD(E.BAREME,7,'*')
---------------------
CASEWHENE.NUMCHEFISNULLTHEN'*******'ELSEC.NOMEND
--------------------------------------------------------------------------------
CURTIS
70000**
CURTIS

CELARIE
80000**
CELARIE

BEART
90000**
BEART

Page :   2                     Liste des employes                 User: JAVAUXRA

NOM
--------------------------------------------------------------------------------
RPAD(E.BAREME,7,'*')
---------------------
CASEWHENE.NUMCHEFISNULLTHEN'*******'ELSEC.NOMEND
--------------------------------------------------------------------------------

HOFFMAN
60000**
HOFFMAN

CLAVIER
65000**
CLAVIER

LAFONT
90000**

Page :   3                     Liste des employes                 User: JAVAUXRA

NOM
--------------------------------------------------------------------------------
RPAD(E.BAREME,7,'*')
---------------------
CASEWHENE.NUMCHEFISNULLTHEN'*******'ELSEC.NOMEND
--------------------------------------------------------------------------------
LAFONT

DE NIRO
88000**
DE NIRO

STALLONE
95000**
STALLONE

BERTHIER

Page :   4                     Liste des employes                 User: JAVAUXRA

NOM
--------------------------------------------------------------------------------
RPAD(E.BAREME,7,'*')
---------------------
CASEWHENE.NUMCHEFISNULLTHEN'*******'ELSEC.NOMEND
--------------------------------------------------------------------------------
67000**
BERTHIER

REDFORD
99000**
REDFORD

MOORE
54000**
MOORE


Page :   5                     Liste des employes                 User: JAVAUXRA

NOM
--------------------------------------------------------------------------------
RPAD(E.BAREME,7,'*')
---------------------
CASEWHENE.NUMCHEFISNULLTHEN'*******'ELSEC.NOMEND
--------------------------------------------------------------------------------
BOHRINGER
66000**
BOHRINGER

LHERMITTE
56700**
*******

MONROE

*******

Page :   6                     Liste des employes                 User: JAVAUXRA

NOM
--------------------------------------------------------------------------------
RPAD(E.BAREME,7,'*')
---------------------
CASEWHENE.NUMCHEFISNULLTHEN'*******'ELSEC.NOMEND
--------------------------------------------------------------------------------


14 rows selected.

