include $(ORACLE_HOME)/precomp/lib/env_precomp.mk

build:	$(COBS)
	cobol -o $(EXE)   $(COBS)  -L$(LIBHOME) $(COBSQLINTF)\
 $(COBOL_PRODLDLIBS) $(PROLDLIBS)
#
# The macro definition fill in some details or override some defaults from 
# other files.
#
otTFLAGS=$(PCCFLAGS)
CLIBS= $(TTLIBS_QA) $(LDLIBS)
PRODUCT_LIBHOME=
MAKEFILE=$(ORACLE_HOME)/precomp/demo/proc/demo_proc.mk
PROCPLSFLAGS= sqlcheck=full userid=$(USERID)
##
CCPSYSINCLUDE=sys_include='(/usr/include/cxx,/usr/include)'
## 
PROCPPFLAGS= code=cpp $(CCPSYSINCLUDE)
NETWORKHOME=$(ORACLE_HOME)/network/
PLSQLHOME=$(ORACLE_HOME)/plsql/
INCLUDE=$(I_SYM). $(I_SYM)$(PRECOMPHOME)public $(I_SYM)$(RDBMSHOME)public $(I_SYM)$(RDBMSHOME)demo $(I_SYM)$(PLSQLHOME)public $(I_SYM)$(NETWORKHOME)public
I_SYM=-I

LLIBCLNTSH=-lclntsh
PROLDLIBS=$(LLIBCLNTSH)
CPPLDLIBS=$(LLIBCLNTSH)
