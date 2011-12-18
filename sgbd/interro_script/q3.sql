-- Modifie la clé primaire d'un patient

ALTER TABLE MEDECIN DISABLE CONSTRAINT FK_MEDECIN_PATIENT;
ALTER TABLE PATIENT DISABLE CONSTRAINT PK_PATIENT;

UPDATE PATIENT SET NUMPATIENT = '&new' WHERE NUMPATIENT = '&old';
UPDATE MEDECIN SET NUMPATIENT = '&new' WHERE NUMPATIENT = '&old';

ALTER TABLE PATIENT ENABLE CONSTRAINT PK_PATIENT;
ALTER TABLE MEDECIN ENABLE CONSTRAINT FK_MEDECIN_PATIENT;

-- SQL> @q3.sql
-- 
-- Table altered.
-- Table altered.
-- 
-- Enter value for new: AU 04
-- Enter value for old: AU 01
-- old   1: UPDATE PATIENT SET NUMPATIENT = '&new' WHERE NUMPATIENT = '&old'
-- new   1: UPDATE PATIENT SET NUMPATIENT = 'AU 04' WHERE NUMPATIENT = 'AU 01'
--
-- 
-- 1 row updated.
-- 
-- Enter value for new: AU 04
-- Enter value for old: AU 01
-- old   1: UPDATE MEDECIN SET NUMPATIENT = '&new' WHERE NUMPATIENT = '&old'
-- new   1: UPDATE MEDECIN SET NUMPATIENT = 'AU 04' WHERE NUMPATIENT = 'AU 01'
-- 
-- 1 row updated.
-- Table altered.
-- Table altered.
