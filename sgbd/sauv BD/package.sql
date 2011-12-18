--------------------------------------------------------
--  Fichier créé - mardi-mars-01-2011   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table AUTEURS
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."AUTEURS" 
   (	"NUMAUTEUR" NUMBER(3,0), 
	"NOM" VARCHAR2(20 BYTE), 
	"PRENOM" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table A_ECRIT
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."A_ECRIT" 
   (	"NUMAUTEUR" NUMBER(3,0), 
	"NUMOUVRAGE" NUMBER(3,0)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Package GESTIONBD
--------------------------------------------------------

  CREATE OR REPLACE PACKAGE "JAVAUXRA"."GESTIONBD" 
IS
PROCEDURE AjouterUnAuteur
 (NumAuteur IN Auteurs.NumAuteur%TYPE,
  Nom IN Auteurs.Nom%TYPE,
  PreNom IN Auteurs.PreNom%TYPE);

PROCEDURE AjouterA_Ecrit
 (NumAuteur IN A_Ecrit.NumAuteur%TYPE,
  NumOuvrage IN A_Ecrit.NumOuvrage%TYPE);

PROCEDURE SupprimerUnAuteur (NumAuteur IN Auteurs.NumAuteur%TYPE);
END GestionBd;

/

--------------------------------------------------------
--  DDL for Package GESTIONETUDIANTS
--------------------------------------------------------

  CREATE OR REPLACE PACKAGE "JAVAUXRA"."GESTIONETUDIANTS" AS 
  PROCEDURE Rechercher(
    Arg_Matricule VARCHAR2(13)
  );
  PROCEDURE Rechercher(
    Arg_Nom VARCHAR2(50),
    Arg_Prenom VARCHAR2(30)
  );
    
  PROCEDURE Supprimer(
    Arg_Matricule VARCHAR2(13)
  );
  
  PROCEDURE Ajouter(
    Arg_etudiant ETUDIANTS%rowtype
  );
  
  PROCEDURE Modifier(
    Arg_ancien ETUDIANTS%rowtype,
    Arg_nouveau ETUDIANTS%rowtype
  );
  
  PROCEDURE Lister(
    Arg_ancien ETUDIANTS%rowtype,
    Arg_nouveau ETUDIANTS%rowtype
  );
END GESTIONETUDIANTS;

CREATE OR REPLACE PACKAGE BODY GESTIONETUDIANTS AS
  PROCEDURE Rechercher(
      Arg_Matricule VARCHAR2(13)
  ) IS
  DECLARE
    Var_etudiant ETUDIANTS%rowtype;
  BEGIN
    SELECT * INTO Var_etudiant
    FROM ETUDIANTS
    WHERE MATRICULE = Arg_Matricule;
    
    DBMS_OUTPUT.PUT_LINE('Nom: ' || Var_etudiant.NOM
      || ' - Prenom: ' || Var_etudiant.PRENOM);    
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
      RAISE_APPLICATION_ERROR(-20001, 'Aucun enregistrement');
    WHEN OTHERS THEN
      RAISE_APPLICATION_ERROR(-20002, 'Erreur : ' || SQLERRM);
   END Rechercher;

  PROCEDURE Rechercher(
      Arg_Nom VARCHAR2(50),
      Arg_Prenom VARCHAR2(30)
  ) IS
  DECLARE
    Var_etudiant ETUDIANTS%rowtype;
  BEGIN
    SELECT * INTO Var_etudiant
    FROM ETUDIANTS
    WHERE NOM = Arg_Nom
      AND PRENOM = Arg_Prenom;
    
    DBMS_OUTPUT.PUT_LINE('Matricule: ' || Var_etudiant.MATRICULE);    
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
      RAISE_APPLICATION_ERROR(-20001, 'Aucun enregistrement');
    WHEN TOO_MANY_ROWS THEN
      RAISE_APPLICATION_ERROR(-20002, 'Plusieurs enregistrement concordant');
    WHEN OTHERS THEN
      RAISE_APPLICATION_ERROR(-20003, 'Erreur : ' || SQLERRM);
   END Rechercher;
   
  PROCEDURE Supprimer(
       Arg_Matricule VARCHAR2(13)
  ) IS
  DECLARE
    MatriculeInconnu EXCEPTION;
  BEGIN
    --SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
  
    DELETE FROM PARCOURS_HE_SESS
    WHERE MATRICULE = Arg_Matricule;
    
    DELETE FROM PARCOURS_HE
    WHERE MATRICULE = Arg_Matricule
      AND MONTHS_BETWEEN(CURRENT_DATE, DATESORTIE) > 36;
    
    DELETE FROM ETUDIANTS
    WHERE MATRRICULE = Arg_Matricule;
    
    IF SQL%NOTFOUND THEN
      RAISE MatriculeInconnu;
    END IF;
    
    COMMIT;
  EXCEPTION
    WHEN MatriculeInconnu THEN
      RAISE_APPLICATION_ERROR(-20001, 'Aucun enregistrement');
    WHEN OTHERS THEN
      RAISE_APPLICATION_ERROR(-20003, 'Erreur : ' || SQLERRM);
   END Rechercher;
END GESTIONETUDIANTS;

/

