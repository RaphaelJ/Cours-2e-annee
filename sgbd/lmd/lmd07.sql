SELECT P.REFGROUPE, AVG(PS.TOTAL)
FROM PARCOURS_HE P
INNER JOIN PARCOURS_HE_SESS PS
  ON PS.MATRICULE = P.MATRICULE AND PS.ANSCO = P.ANSCO
WHERE p.ANNETUD = 2
  AND PS.SESS = 1
  AND P.ANSCO = 2005
  AND P.REFFORMDET = 'ECO-INF0'
GROUP BY P.REFGROUPE
