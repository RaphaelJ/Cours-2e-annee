-- PREMIERE PARTIE --

-- Permet les médecins avec des patients non existants
ALTER TABLE MEDECIN DISABLE CONSTRAINT FK_MEDECIN_PATIENT;

-- Ajoute deux médecins
INSERT INTO MEDECIN VALUES('0803 1', 'neron@pompiers.com', TO_DATE('2008-03-10', 'YYYY-MM-DD'),
                           '112', 'AU 01');

INSERT INTO MEDECIN VALUES('0805 2', 'caligula@empire.it', TO_DATE('2008-05-10', 'YYYY-MM-DD'),
                           '145', 'CE 01');

-- Ajoute deux patients
INSERT INTO PATIENT VALUES('AU 01', 'Auguste', 123, '0803 1');

INSERT INTO PATIENT VALUES('CE 01', 'Ceasar', 321, '0805 2');

-- Réactive la contraite de référence pour les médecins
ALTER TABLE MEDECIN ENABLE CONSTRAINT FK_MEDECIN_PATIENT;

-- SECONDE PARTIE --

-- Contrainte d'entité : clé unique
INSERT INTO MEDECIN VALUES('0803 1', 'neron@pompiers.com', TO_DATE('2008-03-10', 'YYYY-MM-DD'),
                           '112', 'AU 01');
-- Résultat : ORA-00001: unique constraint (JAVAUXRA.PK_MEDECIN) violated

-- Contraite de référence : patient qui n'existe pas
INSERT INTO MEDECIN VALUES('0101 3', 'hipocrate@chios.gr', TO_DATE('2001-01-20', 'YYYY-MM-DD'),
                           '112', 'CL 01');
-- Résultat : ORA-02291: integrity constraint (JAVAUXRA.FK_MEDECIN_PATIENT) violated - parent key not found

-- Contraite applicatives

--	Spécialité inconnue
INSERT INTO MEDECIN VALUES('0712 4', 'diogene@cyniques.gr', TO_DATE('2007-12-20', 'YYYY-MM-DD'),
                           '175', 'CE 01');
-- Résultat : ORA-02290: check constraint (JAVAUXRA.CK_MEDECIN_SPECIALITE) violated

--	Mauvais numero de patient
INSERT INTO PATIENT VALUES('CX 01', 'Claude', 456, '0805 2');
-- Résultat : ORA-02290: check constraint (JAVAUXRA.CK_PATIENT_NUMPATIENT) violated

--	Patient sans médecin
INSERT INTO PATIENT VALUES('AR 01', 'Aristote', 789, NULL);
-- Résultat : ORA-01400: cannot insert NULL into ("JAVAUXRA"."PATIENT"."GENERALISTE")

--	Médecin sans patient
INSERT INTO MEDECIN VALUES('0712 4', 'socrate@cigue.com', TO_DATE('2007-12-20', 'YYYY-MM-DD'),
                           '112', NULL);
-- Résultat : ORA-01400: cannot insert NULL into ("JAVAUXRA"."MEDECIN"."NUMPATIENT")

--	Mauvais numéro de médecin
INSERT INTO MEDECIN VALUES('0412 4', 'platon@dialogues.com', TO_DATE('2002-12-20', 'YYYY-MM-DD'),
                           '112', 'CE 01');
-- Résultat : ORA-02290: check constraint (JAVAUXRA.CK_MEDECIN_NUMMEDECIN) violated


