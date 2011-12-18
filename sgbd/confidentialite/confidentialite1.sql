GRANT SELECT ON ETUDIANTS TO KNUTSGA;

SELECT * FROM ALL_TAB_PRIVS WHERE table_name = 'ETUDIANTS';
-- Affiche les droits accordés sur la table étudiants

SELECT * FROM TABLE_PRIVILEGES WHERE table_name = 'ETUDIANTS'
-- Affiche la liste des types de privilèges accordés à la
-- table étudiants

REVOKE SELECT ON ETUDIANTS FROM KNUTSGA;

SELECT * FROM ALL_TAB_PRIVS WHERE table_name = 'ETUDIANTS';
