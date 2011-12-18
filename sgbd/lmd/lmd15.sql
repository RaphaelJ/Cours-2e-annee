SELECT E.NOM, E.PRENOM, P.RESULTAT
FROM PARCOURS_HE P
INNER JOIN ETUDIANTS E
  USING (MATRICULE)
INNER JOIN PARCOURS_HE_SESS PS
  USING (MATRICULE, ANSCO)
WHERE P.RESULTAT = 'R60'
  AND P.REFFORMDET = 'ECO-INF0'
  AND P.ANNETUD = 3
  AND P.ANSCO = 2007
  AND PS.MENTION = 'SAT'