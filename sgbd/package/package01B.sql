CREATE OR REPLACE PACKAGE GESTIONETUDIANTS AS
  TYPE RET_ETUDIANTS IS TABLE OF ETUDIANTS%ROWTYPE;

  FUNCTION Rechercher(
    Arg_Matricule ETUDIANTS.MATRICULE%TYPE
  ) RETURN ETUDIANTS%ROWTYPE;
  FUNCTION Rechercher(
    Arg_Nom ETUDIANTS.NOM%TYPE,
    Arg_Prenom ETUDIANTS.PRENOM%TYPE
  ) RETURN ETUDIANTS%ROWTYPE;
    
  PROCEDURE Supprimer(
    Arg_Matricule ETUDIANTS.MATRICULE%TYPE
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
  FUNCTION Rechercher(
    Arg_Matricule ETUDIANTS.MATRICULE%TYPE
  ) RETURN ETUDIANTS%ROWTYPE
  AS
  DECLARE
    Var_etudiant ETUDIANTS%rowtype;
    
    MatriculeNullException EXCEPTION;
  BEGIN
    IF Arg_matricule IS NULL THEN;
      RAISE MatriculeNullException;
    END IF;
    
    SELECT * INTO Var_etudiant
    FROM ETUDIANTS
    WHERE MATRICULE = Arg_Matricule;
    
    RETURN Var_etudiant;
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
      RAISE_APPLICATION_ERROR(-20001, 'Aucun enregistrement');
    WHEN MatriculeNullException THEN
      RAISE_APPLICATION_ERROR(-20002, 'Matricule ne peut être null');
    WHEN OTHERS THEN
      RAISE_APPLICATION_ERROR(-20099, 'Erreur : ' || SQLERRM);
   END Rechercher;

  FUNCTION Rechercher(
    Arg_Nom ETUDIANTS.NOM%TYPE,
    Arg_Prenom ETUDIANTS.PRENOM%TYPE
  ) RETURN ETUDIANTS%ROWTYPE
  AS
  DECLARE
    Var_etudiant ETUDIANTS%rowtype;
    
    NomNullException EXCEPTION;
    PrenomNullException EXCEPTION;
  BEGIN
    IF Arg_Nom IS NULL THEN
      RAISE NomNullException;
    ELSE IF Arg_Prenom IS NULL THEN
      RAISE PrenomNullException;
    END IF;
  
    SELECT * INTO Var_etudiant
    FROM ETUDIANTS
    WHERE NOM = Arg_Nom
      AND PRENOM = Arg_Prenom;
    
    RETURN Var_etudiant;  
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
      RAISE_APPLICATION_ERROR(-20001, 'Aucun enregistrement');
    WHEN TOO_MANY_ROWS THEN
      RAISE_APPLICATION_ERROR(-20002, 'Plusieurs enregistrements concordants');
    WHEN NomNullException THEN
      RAISE_APPLICATION_ERROR(-20003, 'Nom ne peut être null');
    WHEN PrenomNullException THEN
      RAISE_APPLICATION_ERROR(-20004, 'Prenom ne peut être null');
    WHEN OTHERS THEN
      RAISE_APPLICATION_ERROR(-20099, 'Erreur : ' || SQLERRM);
   END Rechercher;
   
  PROCEDURE Supprimer(
       Arg_Matricule VARCHAR2(13)
  ) AS
  DECLARE
    MatriculeInconnu EXCEPTION;
    
     -- Toujours des enregistrements dans PARCOURS_HE
     -- (DELETE ForeignKey Exception)
    Moins36MoisException EXCEPTION;
    PRAGMA EXCEPTION_INIT (Moins36MoisException, -2292);
  BEGIN
    --SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
  
    DELETE FROM PARCOURS_HE_SESS
    WHERE MATRICULE = Arg_Matricule;
    
    DELETE FROM PARCOURS_HE
    WHERE MATRICULE = Arg_Matricule
      AND MONTHS_BETWEEN(CURRENT_DATE, DATESORTIE) > 36;
    
    DELETE FROM ETUDIANTS -> code -2292
    WHERE MATRRICULE = Arg_Matricule;
    
    IF SQL%NOTFOUND THEN
      RAISE MatriculeInconnu;
    END IF;
    
    COMMIT;
  EXCEPTION
    WHEN MatriculeInconnu THEN
      RAISE_APPLICATION_ERROR(-20001, 'Aucun enregistrement');
    WHEN Moins36MoisException THEN
      RAISE_APPLICATION_ERROR(-20001, 'L''élève doit être sorti depuis 36 mois');
    WHEN OTHERS THEN
      RAISE_APPLICATION_ERROR(-20099, 'Erreur : ' || SQLERRM);
   END Supprimer;
   
  PROCEDURE Ajouter(
    Arg_etudiant ETUDIANTS%rowtype
  ) AS
  DECLARE
    MatriculeInconnu EXCEPTION;   
    
    NotNullException EXCEPTION; 
    PRAGMA EXCEPTION_INIT (NotNullException, -1400);
    
    CheckException EXCEPTION; 
    PRAGMA EXCEPTION_INIT (CheckException, -2290);
    
    ForeignKeyException EXCEPTION; 
    PRAGMA EXCEPTION_INIT (ForeignKeyException, -2291);
  BEGIN    
    INSERT INTO ETUDIANTS VALUES Arg_etudiant;
    COMMIT;
  EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN
      RAISE_APPLICATION_ERROR(-20001, 'Clé primaire: ' || SQLERRM);
    WHEN NotNullException THEN
      IF INSTR(SQLERRM, "ETATCIVIL") > 0 THEN
        RAISE_APPLICATION_ERROR(-20011, 'ETATCIVIL doit être connu');
      ELSE IF INSTR(SQLERRM, "SITUATION") > 0 THEN
        RAISE_APPLICATION_ERROR(-20012, 'SITUATION doit être connu');
      ELSE IF INSTR(SQLERRM, "CODEPAYSDOM") > 0 THEN
        RAISE_APPLICATION_ERROR(-20013, 'CODEPAYSDOM doit être connu');
      ELSE IF INSTR(SQLERRM, "CODEPAYSNAISSANCE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20014, 'CODEPAYSNAISSANCE doit être connu');
      ELSE IF INSTR(SQLERRM, "DATEENTREE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20015, 'DATEENTREE doit être connu');
      ELSE IF INSTR(SQLERRM, "DATENAISSANCE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20016, 'DATENAISSANVCE doit être connu');
      ELSE IF INSTR(SQLERRM, "LIEUNAISSANCE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20017, 'LIEUNAISSANCE doit être connu');
      ELSE IF INSTR(SQLERRM, "LOCALITEDOM") > 0 THEN
        RAISE_APPLICATION_ERROR(-20018, 'LOCALITEDOM doit être connu');
      ELSE IF INSTR(SQLERRM, "NATIONALITE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20019, 'NATIONALITE doit être connu');
      ELSE IF INSTR(SQLERRM, "NOM") > 0 THEN
        RAISE_APPLICATION_ERROR(-20020, 'NOM doit être connu');
      ELSE IF INSTR(SQLERRM, "PRENOM") > 0 THEN
        RAISE_APPLICATION_ERROR(-20021, 'PRENOM doit être connu');
      ELSE
        RAISE_APPLICATION_ERROR(-20029, 'Certains champs sont obligatoires: ' || SQLERRM);
      END IF;
    WHEN CheckException THEN
      IF INSTR(SQLERRM, "DATEENTREE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20031, 'L''etudiant doit avoir 17 ans');
      ELSE IF INSTR(SQLERRM, "ETATCIVIL") > 0 THEN
        RAISE_APPLICATION_ERROR(-20032, 'ETATCIVIL doit être M ou C');
      ELSE IF INSTR(SQLERRM, "SEXE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20033, 'SEXE doit être M ou F');
      ELSE IF INSTR(SQLERRM, "SITUATION") > 0 THEN
        RAISE_APPLICATION_ERROR(-20034, 'SITUATION doit être I, E ou D');
      ELSE
        RAISE_APPLICATION_ERROR(-20039, 'Erreur lors de la validation d''un des champs: ' || SQLERRM);
      END IF;
    WHEN ForeignKeyException THEN
      IF INSTR(SQLERRM, "COMMUNES") > 0 THEN
        RAISE_APPLICATION_ERROR(-20041, 'Le commune n''existe pas');
      ELSE
        RAISE_APPLICATION_ERROR(-20049, 'Clé étrangère: ' || SQLERRM);
      END IF;
    WHEN OTHERS THEN
      RAISE_APPLICATION_ERROR(-20099, 'Erreur inconnue : ' || SQLERRM);
   END Ajouter;
   
  PROCEDURE Modifier(
    Arg_ancien ETUDIANTS%rowtype,
    Arg_nouveau ETUDIANTS%rowtype
  ) AS
  DECLARE
    Var_etudiant ETUDIANTS%rowtype;
  
    MatriculeChangeException EXCEPTION;
    MatriculeInconnuException EXCEPTION;
    
    VerrouException EXCEPTION;
    PRAGMA EXCEPTION_INIT(VerrouException, -00054);
    
    NotNullException EXCEPTION; 
    PRAGMA EXCEPTION_INIT (NotNullException, -1400);
    
    CheckException EXCEPTION; 
    PRAGMA EXCEPTION_INIT (CheckException, -2290);
    
    ForeignKeyException EXCEPTION; 
    PRAGMA EXCEPTION_INIT (ForeignKeyException, -2291);
  BEGIN
    IF Arg_ancien.MATRICULE = Arg_nouveau.MATRICULE THEN
      RAISE MatriculeChangeException;
    END IF;
    
    SELECT * INTO Var_etudiant
    FROM ETUDIANTS
    WHERE ROW = Arg_ancien
    FOR UPDATE WAIT 5;
    
    UPDATE ETUDIANTS SET ROW = Arg_nouveau
    WHERE MATRICULE = Arg_nouveau.MATRICULE;
    
  EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN
      RAISE_APPLICATION_ERROR(-20001, 'Clé primaire: ' || SQLERRM);
    WHEN NotNullException THEN
      IF INSTR(SQLERRM, "ETATCIVIL") > 0 THEN
        RAISE_APPLICATION_ERROR(-20011, 'ETATCIVIL doit être connu');
      ELSE IF INSTR(SQLERRM, "SITUATION") > 0 THEN
        RAISE_APPLICATION_ERROR(-20012, 'SITUATION doit être connu');
      ELSE IF INSTR(SQLERRM, "CODEPAYSDOM") > 0 THEN
        RAISE_APPLICATION_ERROR(-20013, 'CODEPAYSDOM doit être connu');
      ELSE IF INSTR(SQLERRM, "CODEPAYSNAISSANCE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20014, 'CODEPAYSNAISSANCE doit être connu');
      ELSE IF INSTR(SQLERRM, "DATEENTREE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20015, 'DATEENTREE doit être connu');
      ELSE IF INSTR(SQLERRM, "DATENAISSANCE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20016, 'DATENAISSANVCE doit être connu');
      ELSE IF INSTR(SQLERRM, "LIEUNAISSANCE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20017, 'LIEUNAISSANCE doit être connu');
      ELSE IF INSTR(SQLERRM, "LOCALITEDOM") > 0 THEN
        RAISE_APPLICATION_ERROR(-20018, 'LOCALITEDOM doit être connu');
      ELSE IF INSTR(SQLERRM, "NATIONALITE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20019, 'NATIONALITE doit être connu');
      ELSE IF INSTR(SQLERRM, "NOM") > 0 THEN
        RAISE_APPLICATION_ERROR(-20020, 'NOM doit être connu');
      ELSE IF INSTR(SQLERRM, "PRENOM") > 0 THEN
        RAISE_APPLICATION_ERROR(-20021, 'PRENOM doit être connu');
      ELSE
        RAISE_APPLICATION_ERROR(-20029, 'Certains champs sont obligatoires: ' || SQLERRM);
      END IF;
    WHEN CheckException THEN
      IF INSTR(SQLERRM, "DATEENTREE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20031, 'L''etudiant doit avoir 17 ans');
      ELSE IF INSTR(SQLERRM, "ETATCIVIL") > 0 THEN
        RAISE_APPLICATION_ERROR(-20032, 'ETATCIVIL doit être M ou C');
      ELSE IF INSTR(SQLERRM, "SEXE") > 0 THEN
        RAISE_APPLICATION_ERROR(-20033, 'SEXE doit être M ou F');
      ELSE IF INSTR(SQLERRM, "SITUATION") > 0 THEN
        RAISE_APPLICATION_ERROR(-20034, 'SITUATION doit être I, E ou D');
      ELSE
        RAISE_APPLICATION_ERROR(-20039, 'Erreur lors de la validation d''un des champs: ' || SQLERRM);
      END IF;
    WHEN ForeignKeyException THEN
      IF INSTR(SQLERRM, "COMMUNES") > 0 THEN
        RAISE_APPLICATION_ERROR(-20041, 'Le commune n''existe pas');
      ELSE
        RAISE_APPLICATION_ERROR(-20049, 'Clé étrangère: ' || SQLERRM);
      END IF;
    WHEN NO_DATA_FOUND THEN
      RAISE_APPLICATION_ERROR(-20051, 'Les données ont été modifiées');
    WHEN VerrouException THEN
      RAISE_APPLICATION_ERROR(-20052, 'Les données sont verrouillées en écriture');
    WHEN MatriculeChangeException THEN
      RAISE_APPLICATION_ERROR(-20053, 'Vous ne pouvez pas changer le matricule');
    WHEN MatriculeInconnuException THEN
      RAISE_APPLICATION_ERROR(-20054, 'Le matricule n''existe pas');
    WHEN OTHERS THEN
      RAISE_APPLICATION_ERROR(-20099, 'Erreur inconnue : ' || SQLERRM);
   END Modifier;
   
  FUNCTION Lister(
    Arg_annee_min NUMBER,
    Arg_annee_max NUMBER
  ) RETURN RET_ETUDIANTS
  AS
  DECLARE
    Var_etudiant RET_ETUDIANTS;
  
    AnneesInvalidesException EXCEPTION;
  BEGIN
    IF Arg_annee_min > Arg_annee_max
       OR COALESCE(Arg_annee_min, Arg_annee_max) IS NULL THEN
      RAISE AnneesInvalidesException;
    END IF;
    
    SELECT * INTO Var_etudiants
    FROM ETUDIANTS
    WHERE EXTRACT(YEAR FROM DATENAISSANCE)
      BETWEEN Arg_annee_min AND Arg_annee_max;
    
    RETURN Var_etudiants;    
  EXCEPTION
    WHEN AnneesInvalidesException THEN
      RAISE_APPLICATION_ERROR(-20001, 'Annee min doit etre plus grande que annee max et non nulle');
    WHEN NO_DATA_FOUND THEN
      RAISE_APPLICATION_ERROR(-20002, 'Aucun élève correspondant');
    WHEN OTHERS THEN
      RAISE_APPLICATION_ERROR(-20099, 'Erreur inconnue : ' || SQLERRM);
   END Lister;
END GESTIONETUDIANTS;