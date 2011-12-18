SELECT E.MATRICULE, E.NOM, E.PRENOM, P.ANSCO, S.TOTAL, P.REFFORMDET
FROM ETUDIANTS E
INNER JOIN PARCOURS_HE P
	USING (MATRICULE)
INNER JOIN PARCOURS_HE_SESS S
	USING (MATRICULE, ANSCO)
WHERE S.TOTAL >= (SELECT S2.TOTAL
	FROM PARCOURS_HE_SESS S2
	WHERE S2.ANSCO = S.ANSCO);

SELECT E.MATRICULE, E.NOM, E.PRENOM, P.ANSCO, S.TOTAL, P.REFFORMDET
FROM ETUDIANTS E
INNER JOIN PARCOURS_HE P
        USING (MATRICULE)
INNER JOIN PARCOURS_HE_SESS S
        USING (MATRICULE, ANSCO)
WHERE S.TOTAL >= (SELECT S2.TOTAL
        FROM PARCOURS_HE_SESS S2
	INNER JOIN PARCOURS_HE P2
 	       USING (MATRICULE, ANSCO)
        WHERE P2.ANNETUD = P.ANNETUD);

SELECT E.MATRICULE, E.NOM, E.PRENOM, P.ANSCO, S.TOTAL, P.REFFORMDET
FROM ETUDIANTS E
INNER JOIN PARCOURS_HE P
        USING (MATRICULE)
INNER JOIN PARCOURS_HE_SESS S
        USING (MATRICULE, ANSCO)
WHERE S.TOTAL >= (SELECT S2.TOTAL
        FROM PARCOURS_HE_SESS S2
        INNER JOIN PARCOURS_HE P2
               USING (MATRICULE, ANSCO)
        WHERE P2.REFFORMDET = P.REFFORMDET);
 
