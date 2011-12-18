IDENTIFICATION DIVISION.
PROGRAM-ID. ReportRupture.
ENVIRONMENT DIVISION.
CONFIGURATION SECTION.
SPECIAL-NAMES.
   DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
       SELECT f-input	ASSIGN TO "Etudiants95.dat"
							ORGANIZATION LINE SEQUENTIAL 
                       FILE STATUS IS file-statut.               
       SELECT f-temp	ASSIGN TO "Temp.res".
       SELECT f-output	ASSIGN TO "Rapport.res".               
       SELECT f-sort	ASSIGN TO "sortwk".
DATA DIVISION.
FILE SECTION.
FD     f-input.
       COPY "Etudiants.cpy".
FD     f-temp.
       COPY "Etudiants.cpy" REPLACING enreg-etudiant BY rc-foutput.
FD     f-output REPORT IS rapport_etudiant.
SD     f-sort.
       COPY "Etudiants.cpy" REPLACING enreg-etudiant BY rec-fsort.
WORKING-STORAGE SECTION.
77  file-statut PIC XX.
01  nbre-rec PIC S9(4) BINARY VALUE 1.
01  date-jour.
    02 annee PIC 99.
    02 mois  PIC 99.
    02 jour  PIC 99.
01   eof PIC 9.
     88 eof-true VALUE 1.
     88 eof-false VALUE 0.
* Total calculé automatiquement par report system
* remis à zéro lors du CONTROL FOOTING FINAL
* doit être sauvé
01  total-rec-sauv PIC Z.ZZZ.
REPORT SECTION.
RD  rapport-etudiant  PAGE LIMIT IS 66
                      HEADING        1
                      FIRST DETAIL   5
                      LAST DETAIL   42
                      FOOTING       45 
    CONTROLS ARE FINAL, institut OF f-temp, type-graduat OF f-temp,
                 annee-etude OF f-temp, nr-groupe OF f-temp.
01  report-header TYPE IS REPORT HEADING NEXT GROUP NEXT PAGE.
    02   LINE 24.
         03  COLUMN 20 PIC X(30) VALUE ALL "*".
    02   LINE 25.
         03  COLUMN 20 PIC X(30) VALUE "   SERVICE ELEVES INPRES  ".
    02   LINE 26.
         03  COLUMN 20 PIC X(30) VALUE  ALL "*".

01  TYPE IS PAGE HEADING.
    02   LINE PLUS 2.
         03  COLUMN 4 PIC X(41) 
           VALUE "Liste du nombre d'etudiants a la date du ".
         03  COLUMN 45 PIC 99 SOURCE jour.
         03  COLUMN 47 PIC X VALUE "/".
         03  COLUMN 48 PIC 99 SOURCE mois.
         03  COLUMN 50 PIC X VALUE "/".
         03  COLUMN 51 PIC 99 SOURCE annee.
         03  COLUMN 55 PIC X(5) VALUE "Page:".
         03  COLUMN 61 PIC ZZZ9 SOURCE PAGE-COUNTER.

01  TYPE IS CONTROL HEADING type-graduat OF f-temp.
    02   LINE PLUS 1.
         03 COLUMN 1 PIC X(8) VALUE "Graduat:".
         03 COLUMN 10 PIC 99 SOURCE type-graduat OF f-temp.
01  TYPE IS CONTROL HEADING annee-etude OF f-temp.
    02   LINE PLUS 1.
         03 COLUMN 15 PIC X(6) VALUE "Annee:".
         03 COLUMN 22 PIC X SOURCE annee-etude OF f-temp.
    02   LINE PLUS 1.
         03 COLUMN 30 PIC X(7) VALUE "Section".
01  TYPE IS CONTROL FOOTING nr-groupe OF f-temp.
    02   LINE PLUS 1.
         03 COLUMN 40 PIC X(4) SOURCE num-section OF f-temp.
         03 total-sect COLUMN 45  PIC Z.ZZZ SUM nbre-rec.
01  TYPE IS CONTROL FOOTING annee-etude OF f-temp.
    02   LINE PLUS 1.
         03 COLUMN 15 PIC X(12) VALUE "Total annee:".
         03 total-annee COLUMN 30 PIC Z.ZZZ SUM nbre-rec.
01  TYPE IS CONTROL FOOTING type-graduat OF f-temp NEXT GROUP NEXT PAGE.
    02   LINE PLUS 1.
         03 COLUMN 1 PIC X(14) VALUE "Total graduat:".
         03 total-graduat COLUMN 16 PIC Z.ZZZ SUM total-annee.
01  TYPE IS CONTROL FOOTING institut OF f-temp NEXT GROUP NEXT PAGE.
    02   LINE PLUS 1.
         03 COLUMN 1 PIC X(15) VALUE "Total institut:".
         03 total-institut COLUMN 16 PIC Z.ZZZ SUM total-graduat.

01  TYPE IS CONTROL FOOTING FINAL LINE PLUS 3.
* pas de clause COLUMN donc zone non imprimée
    02 total-rec               PIC Z.ZZZ SUM nbre-rec.

01  TYPE IS REPORT FOOTING.
    02   LINE 24 ON NEXT PAGE.
         03  COLUMN 20 PIC X(30) VALUE ALL "*".
    02   LINE 25.
         03  COLUMN 20 PIC X(30) VALUE "   SERVICE ELEVES INPRES  ".
    02   LINE 26.
         03  COLUMN 20 PIC X(30) VALUE ALL "*".
    02   LINE 27.
         03   COLUMN 20  PIC X(16)  VALUE "Nbre de pages ".
         03   COLUMN 36  PIC ZZZ9  SOURCE PAGE-COUNTER.
    02   LINE 28.
         03   COLUMN 20  PIC X(16) VALUE "Nbre enreg.lus: ".
         03   COLUMN 36  PIC Z.ZZZ SOURCE total-rec-sauv.


PROCEDURE DIVISION.
DECLARATIVES.
decla1 SECTION.
     USE AFTER STANDARD ERROR PROCEDURE ON f-input.
decla2.
     EVALUATE file-statut 
             WHEN "35" DISPLAY "Fichier d'entree non trouve "
             WHEN OTHER DISPLAY "Erreur d'entree/sortie" 
             file-statut 
     END-EVALUATE
     STOP RUN.
END DECLARATIVES.

pp SECTION. 
debut. 
	     SORT f-sort ON ASCENDING	KEY institut OF rec-fsort,
                                         type-graduat OF rec-fsort,
                                         annee-etude OF rec-fsort,
                                         nr-groupe OF rec-fsort,
                                         nom OF rec-fsort

			   USING f-input
			   GIVING  f-temp

     ACCEPT date-jour FROM DATE
     OPEN input f-temp         
     OPEN output f-output
     INITIATE rapport-etudiant
     COMPUTE PAGE_COUNTER = PAGE_COUNTER - 1 

     SET eof-false TO TRUE
     READ f-temp AT END SET eof-true TO TRUE
     END-READ
     PERFORM  TEST BEFORE UNTIL eof-true
       GENERATE rapport-etudiant
       READ f-temp AT END SET eof-true TO TRUE
       END-READ
     END-PERFORM

     COMPUTE PAGE_COUNTER = PAGE_COUNTER - 1. 
     MOVE TOTAL-REC TO TOTAL-REC-SAUV.

     TERMINATE rapport-etudiant
     CLOSE f-temp, f-output
     STOP RUN.
       


