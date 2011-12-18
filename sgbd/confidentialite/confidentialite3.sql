GRANT DELETE ON COMMUNES TO KNUTSGA WITH GRANT OPTION;
GRANT UPDATE (province) ON COMMUNES TO KNUTSGA WITH GRANT OPTION;

SELECT PROVINCE FROM COMMUNES WHERE CODEPOSTAL = 4990 AND LOCALITE = 'BRA';

GRANT SELECT ON ETUDIANTS TO KNUTSGA;
SELECT COUNT(*)
FROM COMMUNES C
LEFT JOIN ETUDIANTS E
	USING (CODEPOSTALDOM, LOCALITEDOM)
WHERE E.CODEPOSTAL IS NULL;

SELECT PROVINCE FROM COMMUNES WHERE CODEPOSTAL = 4030 AND LOCALITE = 'GRIVEGNEE';

SELECT * FROM ALL_TAB_PRIVS WHERE table_name = 'COMMUNES';

REVOKE DELETE ON COMMUNNES FROM  KNUTSGA;
REVOKE  UPDATE (province) ON COMMUNNES FROM  KNUTSGA;
REVOKE SELECT ON ETUDIANTS FROM KNUTSGA;

SELECT * FROM ALL_TAB_PRIVS WHERE table_name = 'COMMUNES';

