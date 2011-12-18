/****************************************************************************
** Form implementation generated from reading ui file 'BorneReservation.ui'
**
** Created: mar. oct. 26 10:06:14 2010
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "BorneReservation.h"

#include "Fichier.ini"
#include "Ecran.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
 
extern int idQ;

#include <qvariant.h>
#include <qtextedit.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a BorneReservation as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
BorneReservation::BorneReservation( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "BorneReservation" );
    setMinimumSize( QSize( 0, 0 ) );
    setMaximumSize( QSize( 1200, 600 ) );

    textPub = new QTextEdit( this, "textPub" );
    textPub->setGeometry( QRect( 20, 20, 760, 90 ) );
    textPub->setReadOnly( TRUE );

    textMenu = new QTextEdit( this, "textMenu" );
    textMenu->setGeometry( QRect( 20, 150, 480, 100 ) );
    textMenu->setReadOnly( TRUE );

    textChoix = new QLabel( this, "textChoix" );
    textChoix->setGeometry( QRect( 520, 150, 180, 20 ) );

    lineChoix = new QLineEdit( this, "lineChoix" );
    lineChoix->setGeometry( QRect( 660, 150, 120, 21 ) );

    ButtonSelectionner = new QPushButton( this, "ButtonSelectionner" );
    ButtonSelectionner->setGeometry( QRect( 520, 210, 120, 29 ) );
    ButtonSelectionner->setAutoDefault( FALSE );

    ButtonAnnuler = new QPushButton( this, "ButtonAnnuler" );
    ButtonAnnuler->setGeometry( QRect( 260, 330, 100, 29 ) );
    ButtonAnnuler->setAutoRepeat( FALSE );
    ButtonAnnuler->setAutoDefault( FALSE );

    ButtonConfirmer = new QPushButton( this, "ButtonConfirmer" );
    ButtonConfirmer->setGeometry( QRect( 100, 330, 100, 29 ) );
    ButtonConfirmer->setAutoDefault( FALSE );

    textNbPlaces = new QLabel( this, "textNbPlaces" );
    textNbPlaces->setGeometry( QRect( 520, 180, 180, 20 ) );

    lineNbPlaces = new QLineEdit( this, "lineNbPlaces" );
    lineNbPlaces->setGeometry( QRect( 720, 180, 60, 20 ) );
    languageChange();
    resize( QSize(800, 400).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( ButtonAnnuler, SIGNAL( pressed() ), this, SLOT( Annuler() ) );
    connect( ButtonConfirmer, SIGNAL( pressed() ), this, SLOT( Confirmer() ) );
    connect( ButtonSelectionner, SIGNAL( pressed() ), this, SLOT( Selectionner() ) );
    connect( lineChoix, SIGNAL( returnPressed() ), this, SLOT( Selectionner() ) );
    connect( lineNbPlaces, SIGNAL( returnPressed() ), this, SLOT( Selectionner() ) );

AffichagePublicite("\nVoici Dossier Unix\n(Janvier 2011)");
AffichageMenu("1 - Concert\n2 - Théatre\n3 - Restaurant");
}

/*
 *  Destroys the object and frees any allocated resources
 */
BorneReservation::~BorneReservation()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void BorneReservation::languageChange()
{
    setCaption( tr( "Borne Reservation" ) );
    textChoix->setText( tr( "Votre choix:" ) );
    ButtonSelectionner->setText( tr( "Selectionner" ) );
    ButtonAnnuler->setText( tr( "Annuler" ) );
    ButtonConfirmer->setText( tr( "Confirmer" ) );
    textNbPlaces->setText( tr( "Nombre de places:" ) );
}

extern   int	idReservation ;

void BorneReservation::Selectionner()
{
Trace("BorneReservation::Selectionner()" );
char	Choix[80];
char	Places[80];
int	NbP,NbC;
DEMANDE	D;

alarm(0);
D.Request = CONSULT;

strcpy(Choix,lineChoix->text());
NbC = atoi(Choix);
if (!NbC)
   { lineChoix->clear();
     lineNbPlaces->clear();
     return;
   }

strcpy(Places,lineNbPlaces->text());
NbP = atoi(Places);
if (!NbP)
   { D.lType = 1;
     D.idProcess = getpid();
     D.Message[0] = NbC;
int 	rc;
     if ((rc = msgsnd(idQ,&D,sizeof(D) - sizeof(long),0)) == -1)
        { perror("(1) Erreur de msgsnd()...");
          exit(1);
        }
Trace("MessageEmis\n");
     D.lType = getpid();
     if (NbC == 1)
        { MSCONCERT	C;
          if ((rc = msgrcv(idQ,&C,sizeof(C) - sizeof(long),getpid(),0)) == -1)
             { perror("(2) Erreur de msgrcv()...");
               exit(1);
             }
          textMenu->clear();
     idReservation = C.idProcess;
     char	Buff[1000];
     char	B[1000];
     Buff[0] = '\0';
     int i = 0,
         Nb = (rc - sizeof(pid_t) - sizeof(int))/sizeof(CONCERT);
Trace("recu de   %d %d Concerts",idReservation,Nb);
     while (i < Nb)
        { sprintf(B,"%2d - %-20s%s %-20s %3d\n",i+1,
                 C.Concert[i].Nom,C.Concert[i].Date,
                 C.Concert[i].Salle,C.Concert[i].Libre);
          strcat(Buff,B);
          i++;
        }
     AffichageMenu(Buff);
   }
Trace("MessageRecu\n");

alarm(20);
lineChoix->clear();
lineNbPlaces->clear();
return;
}

// cas de la reservation 
D.lType = idReservation;
Trace("Emission a %d",(int)D.lType);
D.idProcess = getpid();
D.Message[0] = NbC;
D.Message[1] = NbP;
if ( msgsnd(idQ,&D,sizeof(D) - sizeof(long),0) == -1)
   { perror("(3) Erreur de msgsnd()...");
     exit(1);
   }
alarm(0);
lineChoix->clear();
lineNbPlaces->clear();
AffichageMenu("1 - Concert\n2 - Théatre\n3 - Restaurant");
}

void BorneReservation::Confirmer()
{
Trace( "BorneReservation::Confirmer()" );
alarm(0);
AffichageMenu("1 - Concert\n2 - Théatre\n3 - Restaurant");
lineChoix->clear();
lineNbPlaces->clear();
idReservation = 0;
}

void BorneReservation::Annuler()
{
Trace( "BorneReservation::Annuler()" );
alarm(0);
AffichageMenu("1 - Concert\n2 - Théatre\n3 - Restaurant");
lineChoix->clear();
lineNbPlaces->clear();

idReservation = 0;
}

void BorneReservation::AffichageMenu(const char* M)
{
Trace( "BorneReservation::AffichageMenu(const char*)" );
textMenu->setText(M);
lineChoix->clear();
lineNbPlaces->clear();
}

void BorneReservation::AffichagePublicite(const char* P)
{
Trace( "BorneReservation::AffichagePublicite(const char*)" );
textPub->setText(P);
}

