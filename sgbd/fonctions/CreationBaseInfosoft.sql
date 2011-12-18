-- Ch.Thiry 
-- CreationBaseInfosoft
DROP TABLE emppro;
DROP TABLE projets;
DROP TABLE Departements CASCADE CONSTRAINTS;
DROP TABLE Employes;
/* cr�ation de la base de donn�es INFOSOFT*/
prompt'Cr�ation de la base de donn�es INFOSOFT';
prompt'****************************************';

prompt'Cr�ation de la table EMPLOYES';

CREATE TABLE Employes
(NumSecu 	VARCHAR2(8) CONSTRAINT CPEmployesNumSecu PRIMARY KEY,
Nom 		VARCHAR2 (30) ,
Prenom		VARCHAR2 (30) ,
DateNais	DATE,
Sexe		CHAR(1)	CONSTRAINT EmployesSexe	CHECK (sexe in ('1','2') ),
Adresse		VARCHAR2 (30),
CodePostal	CHAR (4),
Commune		VARCHAR2 (30),
Bareme		NUMBER(5),
NumDep		VARCHAR2 (6),
NumChef		VARCHAR2 (8) CONSTRAINT REFNumChefINEmployes
		REFERENCES Employes (NumSecu)
);



prompt'Cr�ation de la table DEPARTEMENTS';

CREATE TABLE Departements
(NumDep 	VARCHAR2 (6)  CONSTRAINT CPDepartements PRIMARY KEY,
NomDep		VARCHAR2(40),
NumSecu		VARCHAR2 (8) CONSTRAINT REFDeptNumSecuINEmployes
			REFERENCES Employes (NumSecu)
);


ALTER TABLE Employes ADD CONSTRAINT
		REFEmpNumDepINDepartements
		FOREIGN KEY (NumDep)
		REFERENCES Departements (NumDep);


prompt'Cr�ation de la table PROJETS';

CREATE TABLE Projets
(NumPro 	VARCHAR2 (6)  CONSTRAINT CPProjets PRIMARY KEY ,
NomPro		VARCHAR2(50),
DateDebut	DATE,
Site		VARCHAR2 (30),
NumDep		VARCHAR2 (6) CONSTRAINT REFProjetsNumDepINDepartements
			REFERENCES Departements (NumDep));


prompt'Cr�ation de la table EMPPRO';

CREATE TABLE EmpPro
(NumSecu 	VARCHAR2 (8) CONSTRAINT REFEmpProNumSecuINEmployes
			REFERENCES Employes (NumSecu),
NumPro 	VARCHAR2 (6) CONSTRAINT REFEmpProNumProINProjets
			REFERENCES Projets (NumPro),
Heures		VARCHAR2 (2),
CONSTRAINT CPEmpPro  PRIMARY KEY (NumSecu, NumPro));



prompt'Insertion des donn�es dans la base de donn�es INFOSOFT';
prompt'*******************************************************';




insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('123456', 'CURTIS', 'Tony',	 to_date('1930-02-17' ,'YYYY-MM-DD'),'1',
	'rue Egalit�, 18','4430','ANS',70000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('451278', 'CELARIE', 'Cl�mentine',
to_date('1960-10-10' ,'YYYY-MM-DD'),'2',
	'rue Tige, 7','4040','HERSTAL',
	80000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('654321','BEART', 'Emmanuelle',
	 to_date('1965-04-04' ,'YYYY-MM-DD'),'2',
	'quai Boverie, 102','4000','LIEGE',
	90000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('123457', 'HOFFMAN', 'Dustin',
	 to_date('1949-03-19' ,'YYYY-MM-DD'),'1',
	'rue Lantin, 163','4430','ANS',
	60000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('789999', 'CLAVIER', 'Christian',
	 to_date('1957-11-10' ,'YYYY-MM-DD'),'1',
	'La Batte, 9','4000','LIEGE',
	65000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('864231', 'LAFONT', 'Bernadette',
	 to_date('1945-01-14' ,'YYYY-MM-DD'),'2',
	'rue Vaudr�e, 162','4000','LIEGE',
	90000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('439549', 'DE NIRO', 'Robert',
	 to_date('1950-11-02' ,'YYYY-MM-DD'),'1',
	'rue Bonne Foi, 5','4040','HERSTAL',
	88000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('121212', 'STALLONE','Sylvester', 
	 to_date('1952-01-20' ,'YYYY-MM-DD'),'1',
	'chauss�e Romaine, 174','4300','WAREMME',
	95000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('334410', 'BERTHIER','Marie-Sophie L.', 
	 to_date('1960-02-02' ,'YYYY-MM-DD'),'2',
	'all�e Dubois, 5','4050','CHAUDFONTAINE',
	67000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('935132', 'REDFORD', 'Robert',
	 to_date('1940-02-15' ,'YYYY-MM-DD'),'1',
	'avenue Alouettes, 9','4120','NEUPRE',
	99000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('935133', 'MOORE', 'Demi',
	 to_date('1970-12-15' ,'YYYY-MM-DD'),'2',
	'rue Noisetiers, 9','4120','NEUPRE',
	54000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('192356', 'BOHRINGER', 'Romane',
	 to_date('1970-01-01' ,'YYYY-MM-DD'),'2',
	'rue Bolland, 38','4260','BRAIVES',
	66000); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('192357', 'LHERMITTE', 'Thierry',
	 to_date('1955-12-12' ,'YYYY-MM-DD'),'1',
	'rue Vieux Pr�, 6','4050','CHAUDFONTAINE',
	56700); 
insert into employes
(NumSecu, Nom, Prenom, DateNais, Sexe, Adresse, CodePostal, Commune,Bareme)
values ('999999', 'MONROE', 'Marilyn',NULL,NULL,NULL,NULL,NULL,NULL);



prompt'insertion dans la table DEPARTEMENTS ...';

insert into departements
values ('d00001', 'Applications bureautiques', '935132');
insert into departements
values ('d00002', 'Applications Main Frame', '123456');
insert into departements
values ('d00003', 'Applications telecom', '864231');
insert into departements
values ('d00004', 'Didacticiels', '121212');
insert into departements
values ('d00005', 'Images Numeriques', '999999');


prompt'insertion compl�mentaire dans la table EMPLOYES ...';

prompt' --> chefs de d�partements';
upDATE employes
set numdep = 'd00001'
where numsecu = '935132';
upDATE employes
set numdep = 'd00002'
where numsecu = '123456';
upDATE employes
set numdep = 'd00003'
where numsecu = '864231';
upDATE employes
set numdep = 'd00004'
where numsecu = '121212';
upDATE employes
set numchef = '192357'
where numsecu in ('935132', '123456', '864231', '121212');

prompt' --> les autres';
upDATE employes
set numchef = '935132'
where numsecu = '451278';
upDATE employes
set numdep = 'd00001'
where numsecu = '451278';

upDATE employes
set numchef = '123456'
where numsecu = '439549';
upDATE employes
set numchef = '123456'
where numsecu = '654321';
upDATE employes
set numchef = '654321'
where numsecu = '789999';
upDATE employes
set numdep = 'd00002'
where numsecu in ('439549', '654321','789999');

upDATE employes
set numchef = '864231'
where numsecu = '192356';
upDATE employes
set numchef = '864231'
where numsecu = '334410';
upDATE employes
set numdep = 'd00003'
where numsecu in ('192356', '334410'); 

upDATE employes
set numchef = '121212'
where numsecu = '123457';
upDATE employes
set numchef = '123457'
where numsecu = '935133';
upDATE employes
set numdep = 'd00004'
where numsecu in ('123457', '935133');


prompt'insertion dans la table PROJETS ...';

insert into projets 
values ('p10345', 'ALE',
         to_date('1995-01-05' ,'YYYY-MM-DD'), 'SERAING', 'd00003');
insert into projets 
values ('p10346', 'Etude ODBC',
         to_date('1994-07-12' ,'YYYY-MM-DD'), 'LIEGE', 'd00004');
insert into projets 
values ('p10347', 'Etude 4GL- RALLY',
         to_date('1994-02-01' ,'YYYY-MM-DD'), 'LONDON', 'd00004');
insert into projets 
values ('p10348', 'ASBL Defi',
         to_date('1994-12-15' ,'YYYY-MM-DD'), 'SERAING', 'd00001');
insert into projets 
values ('p10349', 'INPRES Etudiants',
         to_date('1994-10-13' ,'YYYY-MM-DD'), 'LIEGE', 'd00002');
insert into projets 
values ('p10350', 'Salaire',
         to_date('1993-09-19' ,'YYYY-MM-DD'), 'LIEGE', 'd00002');
insert into projets 
values ('p10351', 'Offre Emploi',
         to_date('1994-10-13' ,'YYYY-MM-DD'), 'LIEGE', 'd00001');
insert into projets 
values ('p10352', 'Facturation',
         to_date('1993-09-19' ,'YYYY-MM-DD'), 'LIEGE', 'd00002');



prompt'insertion dans la table EMP_PRO ...';

insert into emppro
values ('451278','p10345','10');
insert into emppro
values ('451278','p10346',  '12' ) ;
insert into emppro
values ('451278','p10349',  '10' ) ;
insert into emppro
values ('451278','p10351',  '8' ) ;

insert into emppro
values ('935132','p10348',  '18' ) ;
insert into emppro
values ('935132','p10351',  '18' ) ;

insert into emppro
values ('123456','p10345',  '15' ) ;
insert into emppro
values ('123456','p10349',  '10' ) ;
insert into emppro
values ('123456','p10350',  '15' ) ;

insert into emppro
values ('654321','p10349',  '15' ) ;
insert into emppro
values ('654321','p10350',  '10' ) ;

insert into emppro
values ('789999','p10350',  '15' ) ;
insert into emppro
values ('789999','p10352',  '15' ) ;

insert into emppro
values ('439549','p10349',  '40' ) ;

insert into emppro
values ('864231','p10345',  '20' ) ;
insert into emppro
values ('864231','p10348',  '10' ) ;
insert into emppro
values ('864231','p10349',  '10' ) ;

insert into emppro
values ('334410','p10352',  '30' ) ;

insert into emppro
values ('192356','p10347',  '10' ) ;
insert into emppro
values ('192356','p10349',  '8' ) ;

insert into emppro
values ('123457','p10346',  '10' ) ;
insert into emppro
values ('123457','p10347',  '15' ) ;
insert into emppro
values ('123457','p10350',  '15' ) ;

insert into emppro
values ('121212','p10346',  '19' ) ;
insert into emppro
values ('121212','p10347',  '19' ) ;


commit;