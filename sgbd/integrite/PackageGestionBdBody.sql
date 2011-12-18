CREATE OR REPLACE PACKAGE BODY GestionBd
AS

PROCEDURE AjouterUnAuteur
 (NumAuteur IN Auteurs.NumAuteur%TYPE
 ,Nom IN Auteurs.Nom%TYPE
 ,PreNom IN Auteurs.PreNom%TYPE)
AS
BEGIN
  INSERT INTO Auteurs (NumAuteur,Nom,Prenom) VALUES (NumAuteur,Nom,PreNom);
  COMMIT;
  DBMS_OUTPUT.PUT_LINE('Tuple ' || NumAuteur || ' ' || Nom || ' ' || Prenom || ' Ajoute'); 
EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN DBMS_OUTPUT.PUT_LINE(SQLCODE ||' '|| SQLERRM );
    WHEN OTHERS THEN DBMS_OUTPUT.PUT_LINE(SQLCODE ||' '|| SQLERRM );
END AjouterUnAuteur;

PROCEDURE AjouterA_Ecrit
 (NumAuteur IN A_Ecrit.NumAuteur%TYPE
 ,NumOuvrage IN A_Ecrit.NumOuvrage%TYPE)
 AS
BEGIN
  INSERT INTO A_Ecrit (NumAuteur,NumOuvrage) VALUES (NumAuteur,NumOuvrage);
 COMMIT;
 DBMS_OUTPUT.PUT_LINE('Tuple ' || NumAuteur || ' ' || NumOuvrage || ' Ajoute');
EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN DBMS_OUTPUT.PUT_LINE(SQLCODE ||' '|| SQLERRM );
    WHEN OTHERS THEN DBMS_OUTPUT.PUT_LINE(SQLCODE ||' '|| SQLERRM );
END AjouterA_Ecrit;

PROCEDURE SupprimerUnAuteur (NumAuteur IN Auteurs.NumAuteur%TYPE)
AS
BEGIN
 DELETE FROM auteurs WHERE NumAuteur = SupprimerUnAuteur.NumAuteur;
 COMMIT;
 DBMS_OUTPUT.PUT_LINE('Tuple ' || NumAuteur || ' Supprime');
EXCEPTION
    WHEN OTHERS THEN DBMS_OUTPUT.PUT_LINE(SQLCODE ||' ' ||  SQLERRM);
END SupprimerUnAuteur; 
  

END GestionBd;
/
