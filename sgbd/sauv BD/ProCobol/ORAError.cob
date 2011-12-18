IDENTIFICATION DIVISION.
PROGRAM-ID. ORAError.
ENVIRONMENT DIVISION.
DATA DIVISION.
LINKAGE SECTION.
01 Sqlstate.
	02 SqlstateClass PIC XX.
		88 SqlstateOk VALUE '00','01','02'.
	02 SqlstateSuite PIC XXX.
PROCEDURE DIVISION USING Sqlstate. 
Debut.
         DISPLAY " " LINE 22 ERASE TO END OF LINE
         DISPLAY "ERREUR SqlState " LINE 23 Sqlstate
         EVALUATE SqlstateClass
         	WHEN "00" DISPLAY "Success Completion " LINE 22 COLUMN 1
		WHEN "01" DISPLAY "Warning " LINE 22 COLUMN 1
		WHEN "02" DISPLAY "No Data " LINE 22 COLUMN 1
		WHEN "07" DISPLAY "Dynamic SQL error " LINE 22 COLUMN 1
		WHEN "08" DISPLAY "Connection Exception " LINE 22 COLUMN 1
		WHEN "0A" DISPLAY "Feature not supported " LINE 22 COLUMN 1
		WHEN "21" DISPLAY "Coordinately Violation " LINE 22 COLUMN 1
		WHEN "22" DISPLAY "Data Exception " LINE 22 COLUMN 1
		WHEN "23" DISPLAY "Integrity Constraint Violation " LINE 22 COLUMN 1
		WHEN "24" DISPLAY "Invalid Cursor State " LINE 22 COLUMN 1
		WHEN "25" DISPLAY "Invalid Transaction State " LINE 22 COLUMN 1
		WHEN "26" DISPLAY "Invalid SQL Statement Name " LINE 22 COLUMN 1
		WHEN "27" DISPLAY "Triggered Data Change Violation " LINE 22 COLUMN 1
		WHEN "28" DISPLAY "Invalid Authorization Specification " LINE 22 COLUMN 1
		WHEN "2A" DISPLAY "Direct SQL syntax error or access rule violation " LINE 22 COLUMN 1
		WHEN "2B" DISPLAY "Dependent privilege descriptors still exist " LINE 22 COLUMN 1
		WHEN "2C" DISPLAY "Invalid character set name" LINE 22 COLUMN 1
		WHEN "2D" DISPLAY "Invalid transaction termination " LINE 22 COLUMN 1
		WHEN "2E" DISPLAY "Invalid Connection name " LINE 22 COLUMN 1
		WHEN "33" DISPLAY "Invalid SQL descriptor name " LINE 22 COLUMN 1
		WHEN "34" DISPLAY "Invalid Cursor Name " LINE 22 COLUMN 1
		WHEN "35" DISPLAY "Invalid condition number " LINE 22 COLUMN 1
		WHEN "37" DISPLAY "Dynamic SQL syntax error or access rule violation " LINE 22 COLUMN 1
		WHEN "3C" DISPLAY "Ambiguous cursor name " LINE 22 COLUMN 1
		WHEN "3D" DISPLAY "Invalid Catalog name " LINE 22 COLUMN 1
		WHEN "3F" DISPLAY "Invalid schema name " LINE 22 COLUMN 1
		WHEN "40" DISPLAY "Transaction rollback " LINE 22 COLUMN 1
		WHEN "42" DISPLAY "Syntax error or access rule violation " LINE 22 COLUMN 1
		WHEN "44" DISPLAY "With check option violation " LINE 22 COLUMN 1
		WHEN "HZ" DISPLAY "Remote database access " LINE 22 COLUMN 1
	 END-EVALUATE	
         EXIT PROGRAM.
         
