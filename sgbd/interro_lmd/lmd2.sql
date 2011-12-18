SELECT REFGROUPE
FROM PARCOURS_HE P
WHERE ANSCO = 2009
  AND ANNETUD = 1
  AND DATESORTIE IS NOT NULL
GROUP BY REFGROUPE
HAVING COUNT(*) > 5