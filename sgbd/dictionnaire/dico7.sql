SET ECHO OFF FEEDBACK OFF HEADING OFF
SPOOL DropTable.sql
SELECT 'DROP TABLE ' || TABLE_NAME || ' CASCADE CONSTRAINTS;'
FROM USER_TABLES;
SPOOL OFF
SET ECHO ON FEEDBACK ON HEADING ON
