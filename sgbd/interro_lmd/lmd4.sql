SELECT E.MATRICULE, E.NOM, E.PRENOM, P.REFFORMDET, S.TOTAL
FROM PARCOURS_HE P
INNER JOIN PARCOURS_HE_SESS S
  ON S.MATRICULE = P.MATRICULE
  AND S.ANSCO = P.ANSCO
INNER JOIN ETUDIANTS E
  ON P.MATRICULE = E.MATRICULE
WHERE P.REFIMPLAN = 'INPS'
  AND P.ANSCO = 2008
  AND S.TOTAL = (SELECT MAX(S2.TOTAL)
    FROM PARCOURS_HE_SESS S2
    INNER JOIN PARCOURS_HE P2
      ON S2.MATRICULE = P2.MATRICULE
      AND S2.ANSCO = P2.ANSCO
    WHERE P2.REFIMPLAN = 'INPS'
      AND P2.ANSCO = 2008
      AND P2.REFFORMDET = P.REFFORMDET)
  
