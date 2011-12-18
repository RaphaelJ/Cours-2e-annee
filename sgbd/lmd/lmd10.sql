SELECT P.ANSCO, COUNT(PS.MATRICULE)
FROM PARCOURS_HE_SESS PS
WHERE PS.SESS = 2
  AND PS.MENTION = 'DIS'
GROUP BY P.ANSCO
HAVING COUNT(PS.MATRICULE) >= 20;

SELECT P.ANSCO
FROM PARCOURS_HE P
GROUP BY ANSCO
HAVING (SELECT COUNT(PS.MATRICULE)
	FROM PARCOURS_HE_SESS PS
	WHERE PS.ANSCO = p.ANSCO
	  AND PS.SESS = 2
	  AND PS.MENTION = 'DIS'
	) >= 20;