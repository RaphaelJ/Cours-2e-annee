SELECT REFGROUPE, COUNT(*)
FROM PARCOURS_HE P
GROUP BY REFGROUPE
HAVING COUNT(*) > 15;
