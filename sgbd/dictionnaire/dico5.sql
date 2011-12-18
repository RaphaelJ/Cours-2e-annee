SELECT CONSTRAINT_NAME, con.SEARCH_CONDITION, col.COLUMN_NAME,
	CASE
		WHEN con.CONSTRAINT_TYPE = 'C' THEN 'CHECK'
		WHEN con.CONSTRAINT_TYPE = 'P' THEN 'PRIMARY'
		WHEN con.CONSTRAINT_TYPE = 'R' THEN 'REFERENTIEL'
		WHEN con.CONSTRAINT_TYPE = 'U' THEN 'UNIQUE'
		ELSE 'INCONNU'
	END
FROM USER_CONSTRAINTS con
INNER JOIN USER_CONS_COLUMNS col
	USING(CONSTRAINT_NAME)
WHERE col.TABLE_NAME = UPPER('&1');
