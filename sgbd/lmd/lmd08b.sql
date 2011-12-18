SELECT P.REFGROUPE, COUNT(E.MATRICULE)
FROM PARCOURS_HE P
INNER JOIN ETUDIANTS E
  ON E.MATRICULE = P.MATRICULE
WHERE p.ANNETUD = 2
  AND P.ANSCO = 2004
  AND P.REFFORMDET = 'TECH-RESE'
GROUP BY P.REFGROUPE
HAVING COUNT(E.MATRICULE) >=ALL(
	SELECT COUNT(E.MATRICULE)
	FROM PARCOURS_HE P
	INNER JOIN ETUDIANTS E
		ON E.MATRICULE = P.MATRICULE
	WHERE p.ANNETUD = 2
	  AND P.ANSCO = 2004
	  AND P.REFFORMDET = 'TECH-RESE'
	GROUP BY P.REFGROUPE);