SELECT STATUS
FROM USER_PROCEDURES
WHERE PROCEDURE_NAME = 'ListeAO';

ALTER TABLE OUVRAGES
	ADD NUMEDITION NUMBER;

SELECT STATUS
FROM USER_PROCEDURES
WHERE PROCEDURE_NAME = 'ListeAO';

EXECUTE ListeAO;
-- La procédure s'exécute toujours car elle est indépendante de
-- la table, à l'exception des colonnes qu'elle utiliser.
-- Si l'on ne fait que rajouter une colonne, la procédure ne doit
-- pas être modifiée.
