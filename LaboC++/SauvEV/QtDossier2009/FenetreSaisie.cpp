/****************************************************************************
** Form implementation generated from reading ui file 'FenetreSaisie.ui'
**
** Created: Sun Nov 1 13:58:00 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "FenetreSaisie.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "Fichier.ini"

#include "FonctionUtile.h"

extern int      idQ;

/*
 *  Constructs a FenetreSaisie as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
FenetreSaisie::FenetreSaisie( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "FenetreSaisie" );

    textTitre = new QLabel( this, "textTitre" );
    textTitre->setGeometry( QRect( 210, 20, 160, 21 ) );
    QFont textTitre_font(  textTitre->font() );
    textTitre_font.setFamily( "Helvetica [Adobe]" );
    textTitre_font.setPointSize( 18 );
    textTitre_font.setBold( TRUE );
    textTitre->setFont( textTitre_font ); 
    textTitre->setAlignment( int( QLabel::AlignCenter ) );

    textNom = new QLabel( this, "textNom" );
    textNom->setGeometry( QRect( 30, 50, 59, 20 ) );

    lineSaisieNom = new QLineEdit( this, "lineSaisieNom" );
    lineSaisieNom->setGeometry( QRect( 100, 50, 220, 20 ) );

    ButtonLogin = new QPushButton( this, "ButtonLogin" );
    ButtonLogin->setGeometry( QRect( 440, 50, 85, 20 ) );
    ButtonLogin->setAutoDefault( FALSE );

    ButtonReservation = new QPushButton( this, "ButtonReservation" );
    ButtonReservation->setGeometry( QRect( 740, 420, 85, 20 ) );
    ButtonReservation->setAutoDefault( FALSE );

    ButtonTerminer = new QPushButton( this, "ButtonTerminer" );
    ButtonTerminer->setGeometry( QRect( 550, 50, 85, 20 ) );
    ButtonTerminer->setAutoDefault( FALSE );

    lineNom[0] = new QLineEdit( this, "lineNom" );
    lineNom[0]->setGeometry( QRect( 30, 110, 220, 20 ) );
    lineNom[0]->setReadOnly( TRUE );
    lineNom[1] = new QLineEdit( this, "lineNom" );
    lineNom[1]->setGeometry( QRect( 30, 135, 220, 20 ) );
    lineNom[1]->setReadOnly( TRUE );
    lineNom[2] = new QLineEdit( this, "lineNom" );
    lineNom[2]->setGeometry( QRect( 30, 160, 220, 20 ) );
    lineNom[2]->setReadOnly( TRUE );

    linePrenom[0] = new QLineEdit( this, "linePrenom" );
    linePrenom[0]->setGeometry( QRect( 260, 110, 160, 20 ) );
    linePrenom[0]->setReadOnly( TRUE );
    linePrenom[1] = new QLineEdit( this, "linePrenom" );
    linePrenom[1]->setGeometry( QRect( 260, 135, 160, 20 ) );
    linePrenom[1]->setReadOnly( TRUE );
    linePrenom[2] = new QLineEdit( this, "linePrenom" );
    linePrenom[2]->setGeometry( QRect( 260, 160, 160, 20 ) );
    linePrenom[2]->setReadOnly( TRUE );

    lineTitre[0] = new QLineEdit( this, "lineTitre" );
    lineTitre[0]->setGeometry( QRect( 430, 110, 290, 20 ) );
    lineTitre[0]->setReadOnly( TRUE );
    lineTitre[1] = new QLineEdit( this, "lineTitre" );
    lineTitre[1]->setGeometry( QRect( 430, 135, 290, 20 ) );
    lineTitre[1]->setReadOnly( TRUE );
    lineTitre[2] = new QLineEdit( this, "lineTitre" );
    lineTitre[2]->setGeometry( QRect( 430, 160, 290, 20 ) );
    lineTitre[2]->setReadOnly( TRUE );

    ButtonRendu[0] = new QPushButton( this, "ButtonRendu" );
    ButtonRendu[0]->setGeometry( QRect( 740, 110, 85, 20 ) );
    ButtonRendu[0]->setAutoDefault( FALSE );
    ButtonRendu[1] = new QPushButton( this, "ButtonRendu" );
    ButtonRendu[1]->setGeometry( QRect( 740, 135, 85, 20 ) );
    ButtonRendu[1]->setAutoDefault( FALSE );
    ButtonRendu[2] = new QPushButton( this, "ButtonRendu" );
    ButtonRendu[2]->setGeometry( QRect( 740, 160, 85, 20 ) );
    ButtonRendu[2]->setAutoDefault( FALSE );

    ButtonPrecedent = new QPushButton( this, "ButtonPrecedent" );
    ButtonPrecedent->setGeometry( QRect( 60, 365, 85, 20 ) );
    ButtonPrecedent->setAutoDefault( FALSE );

    ButtonEffacer = new QPushButton( this, "ButtonEffacer" );
    ButtonEffacer->setGeometry( QRect( 330, 365, 85, 20 ) );
    ButtonEffacer->setAutoDefault( FALSE );

    ButtonSuivant = new QPushButton( this, "ButtonSuivant" );
    ButtonSuivant->setGeometry( QRect( 600, 365, 85, 20 ) );
    ButtonSuivant->setAutoDefault( FALSE );

    lineRecherche = new QLineEdit( this, "lineRecherche" );
    lineRecherche->setGeometry( QRect( 430, 190, 290, 20 ) );

    lineNomOk[0] = new QLineEdit( this, "lineNomOk" );
    lineNomOk[0]->setGeometry( QRect( 30, 230, 220, 20 ) );
    lineNomOk[0]->setReadOnly( TRUE );
    lineNomOk[1] = new QLineEdit( this, "lineNomOk" );
    lineNomOk[1]->setGeometry( QRect( 30, 255, 220, 20 ) );
    lineNomOk[1]->setReadOnly( TRUE );
    lineNomOk[2] = new QLineEdit( this, "lineNomOk" );
    lineNomOk[2]->setGeometry( QRect( 30, 280, 220, 20 ) );
    lineNomOk[2]->setReadOnly( TRUE );
    lineNomOk[3] = new QLineEdit( this, "lineNomOk" );
    lineNomOk[3]->setGeometry( QRect( 30, 305, 220, 20 ) );
    lineNomOk[3]->setReadOnly( TRUE );
    lineNomOk[4] = new QLineEdit( this, "lineNomOk" );
    lineNomOk[4]->setGeometry( QRect( 30, 330, 220, 20 ) );
    lineNomOk[4]->setReadOnly( TRUE );

    linePrenomOk[0] = new QLineEdit( this, "linePrenomOk" );
    linePrenomOk[0]->setGeometry( QRect( 260, 230, 160, 20 ) );
    linePrenomOk[0]->setReadOnly( TRUE );
    linePrenomOk[1] = new QLineEdit( this, "linePrenomOk" );
    linePrenomOk[1]->setGeometry( QRect( 260, 255, 160, 20 ) );
    linePrenomOk[1]->setReadOnly( TRUE );
    linePrenomOk[2] = new QLineEdit( this, "linePrenomOk" );
    linePrenomOk[2]->setGeometry( QRect( 260, 280, 160, 20 ) );
    linePrenomOk[2]->setReadOnly( TRUE );
    linePrenomOk[3] = new QLineEdit( this, "linePrenomOk" );
    linePrenomOk[3]->setGeometry( QRect( 260, 305, 160, 20 ) );
    linePrenomOk[3]->setReadOnly( TRUE );
    linePrenomOk[4] = new QLineEdit( this, "linePrenomOk" );
    linePrenomOk[4]->setGeometry( QRect( 260, 330, 160, 20 ) );
    linePrenomOk[4]->setReadOnly( TRUE );

    lineTitreOk[0] = new QLineEdit( this, "lineTitreOk" );
    lineTitreOk[0]->setGeometry( QRect( 430, 230, 270, 20 ) );
    lineTitreOk[0]->setReadOnly( TRUE );
    lineTitreOk[1] = new QLineEdit( this, "lineTitreOk" );
    lineTitreOk[1]->setGeometry( QRect( 430, 255, 270, 20 ) );
    lineTitreOk[1]->setReadOnly( TRUE );
    lineTitreOk[2] = new QLineEdit( this, "lineTitreOk" );
    lineTitreOk[2]->setGeometry( QRect( 430, 280, 270, 20 ) );
    lineTitreOk[2]->setReadOnly( TRUE );
    lineTitreOk[3] = new QLineEdit( this, "lineTitreOk" );
    lineTitreOk[3]->setGeometry( QRect( 430, 305, 270, 20 ) );
    lineTitreOk[3]->setReadOnly( TRUE );
    lineTitreOk[4] = new QLineEdit( this, "lineTitreOk" );
    lineTitreOk[4]->setGeometry( QRect( 430, 330, 270, 20 ) );
    lineTitreOk[4]->setReadOnly( TRUE );

    lineReserveOk[0] = new QLineEdit( this, "lineReserveOk" );
    lineReserveOk[0]->setGeometry( QRect( 700, 230, 20, 20 ) );
    lineReserveOk[0]->setReadOnly( TRUE );
    lineReserveOk[1] = new QLineEdit( this, "lineReserveOk" );
    lineReserveOk[1]->setGeometry( QRect( 700, 255, 20, 20 ) );
    lineReserveOk[1]->setReadOnly( TRUE );
    lineReserveOk[2] = new QLineEdit( this, "lineReserveOk" );
    lineReserveOk[2]->setGeometry( QRect( 700, 280, 20, 20 ) );
    lineReserveOk[2]->setReadOnly( TRUE );
    lineReserveOk[3] = new QLineEdit( this, "lineReserveOk" );
    lineReserveOk[3]->setGeometry( QRect( 700, 305, 20, 20 ) );
    lineReserveOk[3]->setReadOnly( TRUE );
    lineReserveOk[4] = new QLineEdit( this, "lineReserveOk" );
    lineReserveOk[4]->setGeometry( QRect( 700, 330, 20, 20 ) );
    lineReserveOk[4]->setReadOnly( TRUE );

    ButtonSelectionnerOk[0] = new QPushButton( this, "ButtonSelectionnerOk" );
    ButtonSelectionnerOk[0]->setGeometry( QRect( 740, 230, 85, 20 ) );
    ButtonSelectionnerOk[0]->setAutoDefault( FALSE );
    ButtonSelectionnerOk[1] = new QPushButton( this, "ButtonSelectionnerOk" );
    ButtonSelectionnerOk[1]->setGeometry( QRect( 740, 255, 85, 20 ) );
    ButtonSelectionnerOk[1]->setAutoDefault( FALSE );
    ButtonSelectionnerOk[2] = new QPushButton( this, "ButtonSelectionnerOk" );
    ButtonSelectionnerOk[2]->setGeometry( QRect( 740, 280, 85, 20 ) );
    ButtonSelectionnerOk[2]->setAutoDefault( FALSE );
    ButtonSelectionnerOk[3] = new QPushButton( this, "ButtonSelectionnerOk" );
    ButtonSelectionnerOk[3]->setGeometry( QRect( 740, 305, 85, 20 ) );
    ButtonSelectionnerOk[3]->setAutoDefault( FALSE );
    ButtonSelectionnerOk[4] = new QPushButton( this, "ButtonSelectionnerOk" );
    ButtonSelectionnerOk[4]->setGeometry( QRect( 740, 330, 85, 20 ) );
    ButtonSelectionnerOk[4]->setAutoDefault( FALSE );

    textSaisie = new QLabel( this, "textSaisie" );
    textSaisie->setGeometry( QRect( 30, 190, 330, 20 ) );

    textMessage = new QTextEdit( this, "textMessage" );
    textMessage->setGeometry( QRect( 30, 420, 685, 58 ) );
    textMessage->setReadOnly( TRUE );

    textInformation = new QLabel( this, "textInformation" );
    textInformation->setGeometry( QRect( 30, 390, 80, 20 ) );
    QFont textInformation_font(  textInformation->font() );
    textInformation_font.setFamily( "Helvetica [Adobe]" );
    textInformation_font.setBold( TRUE );
    textInformation->setFont( textInformation_font ); 

    textSelection = new QLabel( this, "textSelection" );
    textSelection->setGeometry( QRect( 30, 80, 180, 20 ) );
    languageChange();
    resize( QSize(850, 500).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( ButtonLogin, SIGNAL( clicked() ), this, SLOT( Login() ) );
    connect( ButtonReservation, SIGNAL( clicked() ), this, SLOT( Reservation() ) );
    connect( lineSaisieNom, SIGNAL( returnPressed() ), this, SLOT( Login() ) );
    connect( ButtonEffacer, SIGNAL( clicked() ), this, SLOT( Effacer() ) );
    connect( ButtonTerminer, SIGNAL( clicked() ), this, SLOT( Terminer() ) );
    connect( ButtonPrecedent, SIGNAL( clicked() ), this, SLOT( Precedent() ) );
    connect( ButtonSuivant, SIGNAL( clicked() ), this, SLOT( Suivant() ) );
    connect( lineRecherche, SIGNAL( returnPressed() ), this, SLOT( Recherche() ) );
    connect( ButtonRendu[0], SIGNAL( clicked() ), this, SLOT( Rendu0() ) );
    connect( ButtonRendu[1], SIGNAL( clicked() ), this, SLOT( Rendu1() ) );
    connect( ButtonRendu[2], SIGNAL( clicked() ), this, SLOT( Rendu2() ) );
    connect( ButtonSelectionnerOk[0], SIGNAL( clicked() ), this, SLOT( SelectionnerOk0() ) );
    connect( ButtonSelectionnerOk[1], SIGNAL( clicked() ), this, SLOT( SelectionnerOk1() ) );
    connect( ButtonSelectionnerOk[2], SIGNAL( clicked() ), this, SLOT( SelectionnerOk2() ) );
    connect( ButtonSelectionnerOk[3], SIGNAL( clicked() ), this, SLOT( SelectionnerOk3() ) );
    connect( ButtonSelectionnerOk[4], SIGNAL( clicked() ), this, SLOT( SelectionnerOk4() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
FenetreSaisie::~FenetreSaisie()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FenetreSaisie::languageChange()
{
    setCaption( tr( "Bibliothèque Inpres" ) );
    textTitre->setText( tr( "Bibliothèque" ) );
    textNom->setText( tr( "Nom :" ) );
    ButtonLogin->setText( tr( "Login" ) );
    ButtonReservation->setText( tr( "Réservation" ) );
    ButtonPrecedent->setText( trUtf8( "\x50\x72\xc3\xa9\x63\xc3\xa9\x64\x65\x6e\x74" ) );
    ButtonEffacer->setText( tr( "Effacer" ) );
    ButtonSuivant->setText( tr( "Suivant" ) );
    ButtonRendu[0]->setText( tr( "Rendu" ) );
    ButtonRendu[1]->setText( tr( "Rendu" ) );
    ButtonRendu[2]->setText( tr( "Rendu" ) );
    ButtonSelectionnerOk[0]->setText( tr( "Selectionner" ) );
    ButtonSelectionnerOk[1]->setText( tr( "Selectionner" ) );
    ButtonSelectionnerOk[2]->setText( tr( "Selectionner" ) );
    ButtonSelectionnerOk[3]->setText( tr( "Selectionner" ) );
    ButtonSelectionnerOk[4]->setText( tr( "Selectionner" ) );
    ButtonTerminer->setText( tr( "Terminer" ) );
    textSaisie->setText( trUtf8( "\x52\x65\x63\x68\x65\x72\x63\x68\x65\x72\x20\x28\x45\x6e\x74\x72\x65\x72\x20\x6c\x65\x20\x6e\x75\x6d\xc3\xa9\x72\x6f\x20\x64\x75\x20\x6c\x69\x76\x72\x65\x20\x6f\x75\x20\x6c\x65\x20\x6e\x6f\x6d\x20\x64\x27\x61\x75\x74\x65\x75\x72\x29" ) );
    textInformation->setText( tr( "Information:" ) );
    textSelection->setText( tr( "Vous etes en possession de :" ) );
}

void FenetreSaisie::Rendu0()
{
Rendu(0);
}

void FenetreSaisie::Rendu1()
{
Rendu(1);
}

void FenetreSaisie::Rendu2()
{
Rendu(2);
}

void FenetreSaisie::SelectionnerOk0()
{
SelectionnerOk(0);
return;
}

void FenetreSaisie::SelectionnerOk1()
{
SelectionnerOk(1);
return;
}

void FenetreSaisie::SelectionnerOk2()
{
SelectionnerOk(2);
return;
}

void FenetreSaisie::SelectionnerOk3()
{
SelectionnerOk(3);
return;
}

void FenetreSaisie::Rendu(int i)
{
Trace("rendu %d",i);
}

void FenetreSaisie::SelectionnerOk4()
{
SelectionnerOk(4);
return;
}

void FenetreSaisie::Login()
{
Trace( "Dans Login()" );
MESSAGE         	M;
int 			rc;

M.Type = 1;
M.Requete = IDENTIFICATION;
M.Pid = getpid();

Trace("Sizeof M %d",sizeof(M));
if ((rc = msgsnd(idQ,&M,sizeof(M) - sizeof(long),0)) == -1)
   { perror("(Magasin) Erreur de msgsnd()...");
     exit(1);
   }

if ((rc = msgrcv(idQ,&M,sizeof(M) - sizeof(long),getpid(),0)) == -1)
   { perror("(Magasin) Erreur de msgrcv()...");
     exit(1);
   }

textMessage->setText(M.N);

return;
}

void FenetreSaisie::Reservation()
{
Trace( "Dans Reservation()" );
return;
}

void FenetreSaisie::Terminer()
{
Trace( "Dans Terminer()" );
return;
}

void FenetreSaisie::SelectionnerOk(int i)
{
Trace("Dans SelectionnerOk : %d",i);
return;
}

void FenetreSaisie::Precedent()
{
Trace( "Dans Precedent()" );
return;
}

void FenetreSaisie::Suivant()
{
Trace( "Dans Suivant()" );
return;
}

void FenetreSaisie::Effacer()
{
Trace("Dans Effacer()");
return;
}

void FenetreSaisie::Recherche()
{
Trace("Dans Rechercher()");

//char            Buff[20];
int             Numero,rc;

MESSAGE         	M;
MESSAGELIVRE            M1;
LIVRE           	Livre[5];

//strcpy(Buff,lineRecherche->text());
strcpy(M.N,lineRecherche->text());
M.Type = 1;
M.Requete = RECHERCHE;
M.Pid = getpid();

if ((rc = msgsnd(idQ,&M,sizeof(M),0)) == -1)
   { perror("(Magasin) Erreur de msgsnd()...");
     exit(1);
   }

if ((rc = msgrcv(idQ,&M1,sizeof(M1),getpid(),0)) == -1)
   { perror("(Magasin) Erreur de msgrcv()...");
     exit(1);
   }


memcpy(Livre,M1.L,128);

Trace("M1.Requete = %d %d",M1.Requete, rc);
//sprintf(Buff,"%d",Livre[0].Numero);
//lineNumero[0]->setText(Buff);
lineNomOk[0]->setText(Livre[0].NomAuteur);
linePrenomOk[0]->setText(Livre[0].PrenomAuteur);
lineTitreOk[0]->setText(Livre[0].Titre);
if (Livre[0].Libre)
   lineReserveOk[0]->setText("X");
   else lineReserveOk[0]->setText(" ");

return;
}


