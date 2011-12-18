SELECT REFGROUPE
FROM GROUPES G
WHERE ANSCO = 2009
  AND ANNETUD = 1
  AND 5 < (SELECT COUNT(*)
    FROM PARCOURS_HE P
    WHERE REFGROUPE = G.REFGROUPE
      AND ANSCO = G.ANSCO
      AND ANNETUD = G.ANNETUD
      AND DATESORTIE IS NOT NULL);