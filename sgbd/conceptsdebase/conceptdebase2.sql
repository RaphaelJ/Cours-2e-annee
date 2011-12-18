CREATE INDEX I_OUVRAGES_TITRE
	ON OUVRAGES(TITRE);

EXECUTE ListeAO;

-- L'ajout d'un index ne change pas la représentation logique
-- de la table. La procédure ne doit donc pas être modifiée

-- Pour améliorer les temps de recherches pour les requêtes
-- qui concernent le champ titre de la table ouvrages
