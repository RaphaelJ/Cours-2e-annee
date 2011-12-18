SELECT MATRICULE, NOM, PRENOM, TO_CHAR(DATENAISSANCE, 'DD/MM/YYYY')
FROM ETUDIANTS
WHERE NATIONALITE = 'BE'
AND PRENOM LIKE '%A%EL'
ORDER BY NOM;
UNION
SELECT MATRICULE, NOM, PRENOM, TO_CHAR(DATENAISSANCE, 'DD/MM/YYYY')
FROM ETUDIANTS
WHERE TO_CHAR(DATENAISSANCE, 'DD') = '09'
  AND SEXE = 'F'
  AND UPPER(LOCALITEDOM) = 'SERAING';


SELECT MATRICULE, NOM, PRENOM, TO_CHAR(DATENAISSANCE, 'DD/MM/YYYY')
FROM ETUDIANTS
WHERE (NATIONALITE = 'BE'
      AND PRENOM LIKE '%A%EL')
  OR (CHAR(DATENAISSANCE, 'DD') = '09'
      AND SEXE = 'F'
      AND UPPER(LOCALITEDOM) = 'SERAING');
