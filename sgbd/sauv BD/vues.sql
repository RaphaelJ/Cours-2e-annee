--------------------------------------------------------
--  Fichier créé - mardi-mars-01-2011   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Synonymn DUAL
--------------------------------------------------------

  CREATE OR REPLACE PUBLIC SYNONYM "DUAL" FOR "SYS"."DUAL";
--------------------------------------------------------
--  DDL for View A
--------------------------------------------------------

  CREATE OR REPLACE FORCE VIEW "JAVAUXRA"."A" ("DUMMY") AS 
  SELECT "DUMMY" FROM DUAL;
--------------------------------------------------------
--  DDL for Table ETUDIANTS
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."ETUDIANTS" 
   (	"MATRICULE" VARCHAR2(13 CHAR), 
	"NOM" VARCHAR2(50 CHAR), 
	"PRENOM" VARCHAR2(30 CHAR), 
	"NATIONALITE" VARCHAR2(3 CHAR), 
	"ETATCIVIL" CHAR(1 BYTE), 
	"SEXE" CHAR(1 BYTE), 
	"SITUATION" CHAR(1 BYTE), 
	"DATEENTREE" DATE, 
	"DATENAISSANCE" DATE, 
	"LIEUNAISSANCE" VARCHAR2(50 CHAR), 
	"CODEPAYSNAISSANCE" VARCHAR2(3 CHAR), 
	"DATEDECES" DATE, 
	"CODEPOSTALDOM" VARCHAR2(10 CHAR), 
	"LOCALITEDOM" VARCHAR2(50 CHAR), 
	"CODEPAYSDOM" VARCHAR2(3 CHAR)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table PARCOURS_HE
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."PARCOURS_HE" 
   (	"MATRICULE" VARCHAR2(13 CHAR), 
	"ANSCO" VARCHAR2(4 CHAR), 
	"ANNETUD" NUMBER(1,0), 
	"REFFORMDET" VARCHAR2(16 CHAR), 
	"REFIMPLAN" VARCHAR2(10 CHAR), 
	"DATEINSCRIPTION" DATE, 
	"REFGROUPE" VARCHAR2(32 CHAR), 
	"DATESORTIE" DATE, 
	"RESULTAT" VARCHAR2(5 CHAR)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for View V_ETUDIANTS_GROUPE
--------------------------------------------------------

  CREATE OR REPLACE FORCE VIEW "JAVAUXRA"."V_ETUDIANTS_GROUPE" ("MATRICULE", "NOM", "PRENOM", "NATIONALITE", "ETATCIVIL", "SEXE", "SITUATION", "DATEENTREE", "DATENAISSANCE", "LIEUNAISSANCE", "CODEPAYSNAISSANCE", "DATEDECES", "CODEPOSTALDOM", "LOCALITEDOM", "CODEPAYSDOM") AS 
  SELECT E."MATRICULE",E."NOM",E."PRENOM",E."NATIONALITE",E."ETATCIVIL",E."SEXE",E."SITUATION",E."DATEENTREE",E."DATENAISSANCE",E."LIEUNAISSANCE",E."CODEPAYSNAISSANCE",E."DATEDECES",E."CODEPOSTALDOM",E."LOCALITEDOM",E."CODEPAYSDOM"
  FROM ETUDIANTS E
  INNER JOIN PARCOURS_HE P
    ON E.MATRICULE = P.MATRICULE
  WHERE P.ANSCO = 2009
  AND P.REFGROUPE = (SELECT P.REFGROUPE
    FROM ETUDIANTS E
    INNER JOIN PARCOURS_HE P
      ON E.MATRICULE = P.MATRICULE
    WHERE P.ANSCO = 2009
    AND UPPER(E.NOM || SUBSTR(E.PRENOM, 0, 2)) = USER);
--------------------------------------------------------
--  DDL for View V_GROUPES_COMMUNE
--------------------------------------------------------

  CREATE OR REPLACE FORCE VIEW "JAVAUXRA"."V_GROUPES_COMMUNE" ("REFGROUPE", "NBRE_ETUDS") AS 
  SELECT P.REFGROUPE, COUNT(P.REFGROUPE) AS NBRE_ETUDS
  FROM ETUDIANTS E
  INNER JOIN PARCOURS_HE P
    ON E.MATRICULE = P.MATRICULE
  WHERE P.ANSCO = 2009
  AND E.LOCALITEDOM = (SELECT E.LOCALITEDOM
    FROM ETUDIANTS E
    WHERE UPPER(E.NOM || SUBSTR(E.PRENOM, 0, 2)) = USER)
  GROUP BY P.REFGROUPE;
--------------------------------------------------------
--  DDL for Table PARCOURS_HE_SESS
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."PARCOURS_HE_SESS" 
   (	"MATRICULE" VARCHAR2(13 CHAR), 
	"ANSCO" VARCHAR2(4 CHAR), 
	"SESS" NUMBER(1,0), 
	"TOTAL" NUMBER(3,0), 
	"MENTION" VARCHAR2(4 CHAR)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for View V_HISTORIQUE
--------------------------------------------------------

  CREATE OR REPLACE FORCE VIEW "JAVAUXRA"."V_HISTORIQUE" ("MATRICULE", "NOM", "PRENOM", "NATIONALITE", "ETATCIVIL", "SEXE", "SITUATION", "DATEENTREE", "DATENAISSANCE", "LIEUNAISSANCE", "CODEPAYSNAISSANCE", "DATEDECES", "CODEPOSTALDOM", "LOCALITEDOM", "CODEPAYSDOM", "ANSCO", "ANNETUD", "RESULTAT", "SESS", "TOTAL") AS 
  (
  SELECT E."MATRICULE",E."NOM",E."PRENOM",E."NATIONALITE",E."ETATCIVIL",E."SEXE",E."SITUATION",E."DATEENTREE",E."DATENAISSANCE",E."LIEUNAISSANCE",E."CODEPAYSNAISSANCE",E."DATEDECES",E."CODEPOSTALDOM",E."LOCALITEDOM",E."CODEPAYSDOM", P.ANSCO, P.ANNETUD, P.RESULTAT, PS.SESS, PS.TOTAL
  FROM ETUDIANTS E
  INNER JOIN PARCOURS_HE P
    ON P.MATRICULE = E.MATRICULE
  INNER JOIN PARCOURS_HE_SESS PS
    ON PS.MATRICULE = P.MATRICULE
    AND PS.ANSCO = P.ANSCO
  WHERE UPPER(SUBSTR(NOM, 0, 6) || SUBSTR(PRENOM, 0, 2)) = USER
);
--------------------------------------------------------
--  DDL for View V_PARCOURS_HE
--------------------------------------------------------

  CREATE OR REPLACE FORCE VIEW "JAVAUXRA"."V_PARCOURS_HE" ("MATRICULE", "ANSCO", "ANNETUD", "REFFORMDET", "REFIMPLAN", "DATEINSCRIPTION", "REFGROUPE", "DATESORTIE", "RESULTAT") AS 
  SELECT "MATRICULE","ANSCO","ANNETUD","REFFORMDET","REFIMPLAN","DATEINSCRIPTION","REFGROUPE","DATESORTIE","RESULTAT"
  FROM PARCOURS_HE
  WHERE MATRICULE = (SELECT MATRICULE
    FROM ETUDIANTS
    WHERE UPPER(NOM || SUBSTR(PRENOM, 0, 2)) = USER);
--------------------------------------------------------
--  DDL for View V4
--------------------------------------------------------

  CREATE OR REPLACE FORCE VIEW "JAVAUXRA"."V4" ("MATRICULE", "NOM", "PRENOM", "NATIONALITE", "ETATCIVIL", "SEXE", "SITUATION", "DATEENTREE", "DATENAISSANCE", "LIEUNAISSANCE", "CODEPAYSNAISSANCE", "DATEDECES", "CODEPOSTALDOM", "LOCALITEDOM", "CODEPAYSDOM", "ANSCO", "ANNETUD", "REFFORMDET", "REFIMPLAN", "DATEINSCRIPTION", "REFGROUPE", "DATESORTIE", "RESULTAT") AS 
  (SELECT "MATRICULE","NOM","PRENOM","NATIONALITE","ETATCIVIL","SEXE","SITUATION","DATEENTREE","DATENAISSANCE","LIEUNAISSANCE","CODEPAYSNAISSANCE","DATEDECES","CODEPOSTALDOM","LOCALITEDOM","CODEPAYSDOM","ANSCO","ANNETUD","REFFORMDET","REFIMPLAN","DATEINSCRIPTION","REFGROUPE","DATESORTIE","RESULTAT"
FROM ETUDIANTS
NATURAL JOIN PARCOURS_HE);
--------------------------------------------------------
--  DDL for Table COMMUNES
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."COMMUNES" 
   (	"CODEPOSTAL" VARCHAR2(10 CHAR), 
	"LOCALITE" VARCHAR2(50 CHAR), 
	"PROVINCE" VARCHAR2(30 CHAR)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
  GRANT DELETE, UPDATE ("PROVINCE") ON "JAVAUXRA"."COMMUNES" TO "KNUTSGA" WITH GRANT OPTION;
 
  GRANT DELETE, UPDATE ON "JAVAUXRA"."COMMUNES" TO "KNUTSGA" WITH GRANT OPTION;
 

--------------------------------------------------------
--  DDL for View V5
--------------------------------------------------------

  CREATE OR REPLACE FORCE VIEW "JAVAUXRA"."V5" ("MATRICULE", "NOM", "PRENOM", "NATIONALITE", "ETATCIVIL", "SEXE", "SITUATION", "DATEENTREE", "DATENAISSANCE", "LIEUNAISSANCE", "CODEPAYSNAISSANCE", "DATEDECES", "CODEPOSTALDOM", "LOCALITEDOM", "CODEPAYSDOM", "CODEPOSTAL", "LOCALITE", "PROVINCE") AS 
  (SELECT "MATRICULE","NOM","PRENOM","NATIONALITE","ETATCIVIL","SEXE","SITUATION","DATEENTREE","DATENAISSANCE","LIEUNAISSANCE","CODEPAYSNAISSANCE","DATEDECES","CODEPOSTALDOM","LOCALITEDOM","CODEPAYSDOM","CODEPOSTAL","LOCALITE","PROVINCE"
FROM ETUDIANTS, communes
WHERE CODEPAYSDOM = CODEPOSTAL AND LOCALITEDOM = LOCALITE
AND PROVINCE = 'LUXEMBOURG');
--------------------------------------------------------
--  DDL for View V6
--------------------------------------------------------

  CREATE OR REPLACE FORCE VIEW "JAVAUXRA"."V6" ("MATRICULE", "NOM", "PRENOM", "NATIONALITE", "ETATCIVIL", "SEXE", "SITUATION", "DATEENTREE", "DATENAISSANCE", "LIEUNAISSANCE", "CODEPAYSNAISSANCE", "DATEDECES", "CODEPOSTALDOM", "LOCALITEDOM", "CODEPAYSDOM") AS 
  (SELECT "MATRICULE","NOM","PRENOM","NATIONALITE","ETATCIVIL","SEXE","SITUATION","DATEENTREE","DATENAISSANCE","LIEUNAISSANCE","CODEPAYSNAISSANCE","DATEDECES","CODEPOSTALDOM","LOCALITEDOM","CODEPAYSDOM"
FROM ETUDIANTS
WHERE SEXE = 'F'
INTERSECT
SELECT "MATRICULE","NOM","PRENOM","NATIONALITE","ETATCIVIL","SEXE","SITUATION","DATEENTREE","DATENAISSANCE","LIEUNAISSANCE","CODEPAYSNAISSANCE","DATEDECES","CODEPOSTALDOM","LOCALITEDOM","CODEPAYSDOM"
FROM ETUDIANTS
WHERE SITUATION = 'I');
--------------------------------------------------------
--  DDL for View V7
--------------------------------------------------------

  CREATE OR REPLACE FORCE VIEW "JAVAUXRA"."V7" ("MATRICULE", "NOM", "PRENOM", "NATIONALITE", "ETATCIVIL", "SEXE", "SITUATION", "DATEENTREE", "DATENAISSANCE", "LIEUNAISSANCE", "CODEPAYSNAISSANCE", "DATEDECES", "CODEPOSTALDOM", "LOCALITEDOM", "CODEPAYSDOM") AS 
  SELECT "MATRICULE","NOM","PRENOM","NATIONALITE","ETATCIVIL","SEXE","SITUATION","DATEENTREE","DATENAISSANCE","LIEUNAISSANCE","CODEPAYSNAISSANCE","DATEDECES","CODEPOSTALDOM","LOCALITEDOM","CODEPAYSDOM" 
  FROM ETUDIANTS
  WHERE NATIONALITE = 'FRA';
--------------------------------------------------------
--  DDL for View V8
--------------------------------------------------------

  CREATE OR REPLACE FORCE VIEW "JAVAUXRA"."V8" ("MATRICULE", "NOM", "PRENOM", "NATIONALITE", "ETATCIVIL", "SEXE", "SITUATION", "DATEENTREE", "DATENAISSANCE", "LIEUNAISSANCE", "CODEPAYSNAISSANCE", "DATEDECES", "CODEPOSTALDOM", "LOCALITEDOM", "CODEPAYSDOM") AS 
  SELECT "MATRICULE","NOM","PRENOM","NATIONALITE","ETATCIVIL","SEXE","SITUATION","DATEENTREE","DATENAISSANCE","LIEUNAISSANCE","CODEPAYSNAISSANCE","DATEDECES","CODEPOSTALDOM","LOCALITEDOM","CODEPAYSDOM" 
  FROM ETUDIANTS
  WHERE NATIONALITE = 'FRA'
WITH CHECK OPTION;