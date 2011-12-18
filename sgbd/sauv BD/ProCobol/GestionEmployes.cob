IDENTIFICATION DIVISION.
PROGRAM-ID. GestionEmployes.
ENVIRONMENT DIVISION.
DATA DIVISION.
WORKING-STORAGE SECTION.
01  Choix PIC 9.
	88 Fin VALUE 9.
PROCEDURE DIVISION.
BeginPgm.
       	CALL "ORALogon"
       	CALL "MenuEmployes" USING Choix
       	PERFORM TEST BEFORE UNTIL Fin
       		EVALUATE Choix
       			WHEN 1 CALL "AjouterEmployes"
       			WHEN 2 CALL "RechercherEmployes"
       			WHEN 3 CALL "ListerEmployes"
       		END-EVALUATE		
		CALL "MenuEmployes" USING Choix
	END-PERFORM
	CALL "ORALogoff"	
	STOP RUN.
		
           