ALTER TABLE AUTEURS
	ADD CONSTRAINT CK_LONGUEUR_NOM
		CHECK (LENGTH(NOM) > 3 AND LENGTH(NOM) <= 20);

EXECUTE ListeAO

-- Car la procédure ne modifie ou n'ajoute de données qui
-- pourraient ne pas respecter la contrainte. De plus, elle
-- n'utilise pas le colonne titre.
