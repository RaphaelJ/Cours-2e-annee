--------------------------------------------------------
--  Fichier créé - mardi-mars-01-2011   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table CATEGORIES
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."CATEGORIES" 
   (	"REFCATEG" VARCHAR2(10 CHAR), 
	"CATEGORIE" VARCHAR2(50 CHAR), 
	"DIRIGEANT" VARCHAR2(25 CHAR), 
	"TITRE" VARCHAR2(50 CHAR), 
	"SEXE" VARCHAR2(1 CHAR)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index CATEGORIES_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."CATEGORIES_PK" ON "JAVAUXRA"."CATEGORIES" ("REFCATEG") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
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
--  DDL for Index COMMUNES_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."COMMUNES_PK" ON "JAVAUXRA"."COMMUNES" ("CODEPOSTAL", "LOCALITE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table DEPARTEMENTS
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."DEPARTEMENTS" 
   (	"NUMDEP" VARCHAR2(6 BYTE), 
	"NOMDEP" VARCHAR2(40 BYTE), 
	"NUMSECU" VARCHAR2(8 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index CPDEPARTEMENTS
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."CPDEPARTEMENTS" ON "JAVAUXRA"."DEPARTEMENTS" ("NUMDEP") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table DEPT
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."DEPT" 
   (	"DEPTNO" NUMBER(2,0), 
	"DNAME" VARCHAR2(14 BYTE), 
	"LOC" VARCHAR2(13 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index CPDEPT
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."CPDEPT" ON "JAVAUXRA"."DEPT" ("DEPTNO") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table EMPLOYES
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."EMPLOYES" 
   (	"NUMSECU" VARCHAR2(8 BYTE), 
	"NOM" VARCHAR2(30 BYTE), 
	"PRENOM" VARCHAR2(30 BYTE), 
	"DATENAIS" DATE, 
	"SEXE" CHAR(1 BYTE), 
	"ADRESSE" VARCHAR2(30 BYTE), 
	"CODEPOSTAL" CHAR(4 BYTE), 
	"COMMUNE" VARCHAR2(30 BYTE), 
	"BAREME" NUMBER(5,0), 
	"NUMDEP" VARCHAR2(6 BYTE), 
	"NUMCHEF" VARCHAR2(8 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index CPEMPLOYESNUMSECU
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."CPEMPLOYESNUMSECU" ON "JAVAUXRA"."EMPLOYES" ("NUMSECU") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table EMP
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."EMP" 
   (	"EMPNO" NUMBER(4,0), 
	"ENAME" VARCHAR2(10 BYTE), 
	"JOB" CHAR(9 BYTE), 
	"MGR" NUMBER(4,0), 
	"HIREDATE" DATE, 
	"SAL" NUMBER(7,2), 
	"COMM" NUMBER(7,2), 
	"DEPTNO" NUMBER(2,0)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index CPEMPNO
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."CPEMPNO" ON "JAVAUXRA"."EMP" ("EMPNO") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table EMPPRO
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."EMPPRO" 
   (	"NUMSECU" VARCHAR2(8 BYTE), 
	"NUMPRO" VARCHAR2(6 BYTE), 
	"HEURES" VARCHAR2(2 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index CPEMPPRO
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."CPEMPPRO" ON "JAVAUXRA"."EMPPRO" ("NUMSECU", "NUMPRO") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
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
--  DDL for Index CPNUMAUTEUR
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."CPNUMAUTEUR" ON "JAVAUXRA"."AUTEURS" ("NUMAUTEUR") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table OUVRAGES
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."OUVRAGES" 
   (	"NUMOUVRAGE" NUMBER(3,0), 
	"ANNEE" NUMBER(4,0), 
	"TYPEREL" VARCHAR2(10 BYTE), 
	"EDITION" NUMBER, 
	"NUMEDITION" NUMBER, 
	"NUMEDITION2" NUMBER
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index CPNUMOUVRAGE
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."CPNUMOUVRAGE" ON "JAVAUXRA"."OUVRAGES" ("NUMOUVRAGE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table PROJETS
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."PROJETS" 
   (	"NUMPRO" VARCHAR2(6 BYTE), 
	"NOMPRO" VARCHAR2(50 BYTE), 
	"DATEDEBUT" DATE, 
	"SITE" VARCHAR2(30 BYTE), 
	"NUMDEP" VARCHAR2(6 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index CPPROJETS
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."CPPROJETS" ON "JAVAUXRA"."PROJETS" ("NUMPRO") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
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
--  DDL for Index ETUDIANTS_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."ETUDIANTS_PK" ON "JAVAUXRA"."ETUDIANTS" ("MATRICULE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table FORMATIONS_DET
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."FORMATIONS_DET" 
   (	"REFFORMDET" VARCHAR2(16 CHAR), 
	"REFFORMATION" VARCHAR2(16 CHAR), 
	"CYCLE" NUMBER(1,0), 
	"OPT" VARCHAR2(70 CHAR), 
	"FINALITE" VARCHAR2(70 CHAR), 
	"GROUPE" VARCHAR2(70 CHAR), 
	"SOUSSECTION" VARCHAR2(70 CHAR), 
	"ORIENTATION" VARCHAR2(70 CHAR), 
	"ABREVIATION" VARCHAR2(32 CHAR)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index FORMATIONS_DET_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."FORMATIONS_DET_PK" ON "JAVAUXRA"."FORMATIONS_DET" ("REFFORMDET") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table FORMATIONS
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."FORMATIONS" 
   (	"REFFORMATION" VARCHAR2(16 CHAR), 
	"CYCLE" NUMBER(1,0), 
	"FORMATION" VARCHAR2(150 CHAR), 
	"TYPEENS" VARCHAR2(8 CHAR), 
	"REFCATEG" VARCHAR2(10 CHAR), 
	"MAXANNETUD" NUMBER(1,0), 
	"TITRE" VARCHAR2(100 CHAR), 
	"TYPE" VARCHAR2(15 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index FORMATIONS_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."FORMATIONS_PK" ON "JAVAUXRA"."FORMATIONS" ("REFFORMATION", "CYCLE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table GROUPES
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."GROUPES" 
   (	"REFGROUPE" VARCHAR2(32 CHAR), 
	"REFFORMDET" VARCHAR2(16 CHAR), 
	"ANNETUD" NUMBER(1,0), 
	"ANSCO" VARCHAR2(4 CHAR), 
	"REFIMPLAN" VARCHAR2(10 CHAR)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index GROUPES_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."GROUPES_PK" ON "JAVAUXRA"."GROUPES" ("REFGROUPE", "REFFORMDET", "ANNETUD", "ANSCO", "REFIMPLAN") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table IMPLANTATIONS
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."IMPLANTATIONS" 
   (	"REFIMPLAN" VARCHAR2(10 CHAR), 
	"NOMIMPLAN" VARCHAR2(100 CHAR), 
	"ADRESSE" VARCHAR2(75 CHAR), 
	"CODEPOSTAL" VARCHAR2(10 CHAR), 
	"LOCALITE" VARCHAR2(50 CHAR), 
	"TEL" VARCHAR2(13 CHAR)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index IMPLANTATIONS_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."IMPLANTATIONS_PK" ON "JAVAUXRA"."IMPLANTATIONS" ("REFIMPLAN") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table MENTIONS
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."MENTIONS" 
   (	"MENTION" VARCHAR2(4 CHAR), 
	"SESS" NUMBER(1,0), 
	"INTITULE" VARCHAR2(80 CHAR)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index MENTIONS_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."MENTIONS_PK" ON "JAVAUXRA"."MENTIONS" ("MENTION", "SESS") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table ORGANISE
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."ORGANISE" 
   (	"REFFORMDET" VARCHAR2(16 CHAR), 
	"ANNETUD" NUMBER(1,0), 
	"ANSCO" VARCHAR2(4 CHAR), 
	"REFIMPLAN" VARCHAR2(10 CHAR)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index ORGANISE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."ORGANISE_PK" ON "JAVAUXRA"."ORGANISE" ("REFFORMDET", "ANNETUD", "ANSCO", "REFIMPLAN") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
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
--  DDL for Index PARCOURS_HE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."PARCOURS_HE_PK" ON "JAVAUXRA"."PARCOURS_HE" ("MATRICULE", "ANSCO") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
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
--  DDL for Index PARCOURS_HE_SESS_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."PARCOURS_HE_SESS_PK" ON "JAVAUXRA"."PARCOURS_HE_SESS" ("MATRICULE", "ANSCO", "SESS") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table BAREMEMINMAXJAVAUXRA
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."BAREMEMINMAXJAVAUXRA" 
   (	"NUMDEP" VARCHAR2(6 BYTE), 
	"BAREMEMIN" NUMBER, 
	"BAREMEMAX" NUMBER
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index PK_BAREMEMINMAX
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."PK_BAREMEMINMAX" ON "JAVAUXRA"."BAREMEMINMAXJAVAUXRA" ("NUMDEP") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table CLIENTS
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."CLIENTS" 
   (	"IDCLIENT" NUMBER, 
	"NOM" VARCHAR2(20 BYTE), 
	"PRENOM" VARCHAR2(20 BYTE), 
	"VILLE" VARCHAR2(20 BYTE), 
	"CODEPAYS" CHAR(3 BYTE), 
	"SOLDE" NUMBER DEFAULT 0
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index PK_CLIENTS
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."PK_CLIENTS" ON "JAVAUXRA"."CLIENTS" ("IDCLIENT") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table MEDECIN
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."MEDECIN" 
   (	"NUMMEDECIN" CHAR(6 BYTE), 
	"EMAIL" VARCHAR2(20 BYTE), 
	"DATEDIPLOME" DATE, 
	"SPECIALITE" CHAR(3 BYTE), 
	"NUMPATIENT" CHAR(5 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index PK_MEDECIN
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."PK_MEDECIN" ON "JAVAUXRA"."MEDECIN" ("NUMMEDECIN") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table PAYS
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."PAYS" 
   (	"CODEPAYS" CHAR(3 BYTE), 
	"NOM" VARCHAR2(30 BYTE), 
	"DEVISE" VARCHAR2(20 BYTE) DEFAULT 'euro'
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index PK_PAYS
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."PK_PAYS" ON "JAVAUXRA"."PAYS" ("CODEPAYS") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table SEJOURS
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."SEJOURS" 
   (	"IDCLIENT" NUMBER, 
	"VILLAGE" VARCHAR2(20 BYTE), 
	"DATEDEBUT" DATE, 
	"DATEFIN" DATE, 
	"NBPERSONNES" NUMBER
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index PK_SEJOURS
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."PK_SEJOURS" ON "JAVAUXRA"."SEJOURS" ("IDCLIENT", "VILLAGE", "DATEDEBUT") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table STAGES
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."STAGES" 
   (	"VILLAGE" VARCHAR2(20 BYTE), 
	"LIBELLE" VARCHAR2(30 BYTE), 
	"NIVEAU" VARCHAR2(25 BYTE), 
	"PRIX" NUMBER DEFAULT 0
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index PK_STAGES
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."PK_STAGES" ON "JAVAUXRA"."STAGES" ("VILLAGE", "LIBELLE", "NIVEAU") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Table VILLAGES
--------------------------------------------------------

  CREATE TABLE "JAVAUXRA"."VILLAGES" 
   (	"VILLAGE" VARCHAR2(20 BYTE), 
	"NBCHAMBRES" NUMBER DEFAULT 0, 
	"CODEPAYS" CHAR(3 BYTE), 
	"TARIFMIN" NUMBER DEFAULT 0, 
	"TARIFMAX" NUMBER DEFAULT 0, 
	"TRIDENTS" NUMBER DEFAULT 1
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index PK_VILLAGES
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."PK_VILLAGES" ON "JAVAUXRA"."VILLAGES" ("VILLAGE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index UK_CLIENTS_NOM_PRENOM
--------------------------------------------------------

  CREATE UNIQUE INDEX "JAVAUXRA"."UK_CLIENTS_NOM_PRENOM" ON "JAVAUXRA"."CLIENTS" ("PRENOM", "NOM") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
