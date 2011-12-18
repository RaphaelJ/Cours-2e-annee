SELECT P.REFGROUPE
FROM PARCOURS_HE P
WHERE E.ANSCO = 2007
  AND P.ANNETUD = 3
  AND P.REFGROUPE NOT IN IN (SELECT DISTINCT P.REFGROUPE
    FROM PARCOURS_HE P
    INNER JOIN ETUDIANTS E
      USING (MATRICULE)
    WHERE E.SEXE = 'F'
      AND P.ANSCO = 2007
      AND P.ANNETUD = 3)

SELECT P.REFGROUPE
FROM PARCOURS_HE P
INNER JOIN ETUDIANTS E
  USING (MATRICULE)
WHERE E.ANSCO = 2007
  AND P.ANNETUD = 3
  AND NOT EXISTS(SELECT *
    FROM PARCOURS_HE P2
    INNER JOIN ETUDIANTS E2
      USING (MATRICULE)
    WHERE E2.SEXE = 'F'
      AND P2.REFGROUPE = P.REFGROUPE
      AND P2.ANSCO = 2007
      AND P2.ANNETUD = 3)
GROUP BY P.REFGROUPE

SELECT DISTINCT P.REFGROUPE
FROM PARCOURS_HE P
INNER JOIN ETUDIANTS E
  USING (MATRICULE)
WHERE P.ANSCO = 2007
  AND P.ANNETUD = 3
MINUX
SELECT DISTINCT P.REFGROUPE
FROM PARCOURS_HE P
INNER JOIN ETUDIANTS E
  USING (MATRICULE)
WHERE E.SEXE = 'F'
  AND P.ANSCO = 2007
  AND P.ANNETUD = 3

SELECT P.REFGROUPE
FROM PARCOURS_HE P
LEFT JOIN ETUDIANTS E
  ON E.MATRICULE = P.MATRICULE
  AND E.SEXE = 'F'
HAVING COUNT(E.MATRICULE) = 0