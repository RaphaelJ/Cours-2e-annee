GRANT UPDATE, INSERT ON PAYS TO KNUTSGA;

SELECT * FROM ALL_TAB_PRIVS WHERE table_name = 'PAYS';
-- Affiche les droits accordés sur la table pays

SELECT * FROM TABLE_PRIVILEGES WHERE table_name = 'PAYS'
-- Affiche la liste des types de privilèges accordés à la
-- table pays

REVOKE UPDATE, INSERT ON PAYS FROM KNUTSGA;

SELECT * FROM ALL_TAB_PRIVS WHERE table_name = 'ETUDIANTS';
