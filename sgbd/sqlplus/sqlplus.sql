Ex 6 :

SET PAGESIZE  20;
SET LINESIZE 80;

TTITLE LEFT 'Page: ' FORMAT 999 SQL.PNO
       CENTER 'Liste des employés'
       RIGHT 'User: ' SQL.USER
       SKIP 2;

COLUMN EMPNO HEADING 'Nr de l''employé';
COLUMN ENAME HEADING 'Nom de l''employé';
COLUMN HIRDATE HEADING 'Date d''embauche';
COLUMN DNAME HEADING 'Nom du département';

SELECT e.EMPNO, e.ENAME, e.HIREDATE, d.DNAME
FROM EMP e
INNER JOIN DEPT d
  ON d.DEPTNO = e.DEPTNO;

TTITLE OFF;
CLEAR;

Ex 7 :

BREAKE ON DNAME;

SELECT d.DNAME, e.ENAME
FROM DEPT d
LEFT JOIN EMP e
  ON d.DEPTNO = e.DEPTNO
ORDER BY d.DNAME ASC;

CLEAR BREAKS;

Ex 8 : 

INSERT INTO DEPT (DEPTNO, DNAME, LOC)
VALUES ((50, 'Indus et Tele', 'Liège'),
        (60, 'Biochimie', 'Seraing'));

Ex 9 :

SPOOL InsertDepartements;
SET HEADING OFF FEEDBACK OFF ECHO OFF;

SELECT 'INSERT INTO DEPT VALUES('
       || DEPTNO
       || ', ''' || DNAME || ''''
       || ', ''' || LOC || ''');'
FROM DEPT;

SPOOL OFF;
