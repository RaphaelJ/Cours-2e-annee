/****************************************************************************
** Form implementation generated from reading ui file 'FenetreCodePostal.ui'
**
** Created: Thu Oct 8 05:18:01 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "FenetreCodePostal.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "Fichier.ini"
#include "FichierIndex.h"
#include "FonctionUtile.h"

extern FICHIERINDEX	F1;

/*
 *  Constructs a RechercheCodesPostaux as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
RechercheCodesPostaux::RechercheCodesPostaux( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "RechercheCodesPostaux" );

    textTitre = new QLabel( this, "textTitre" );
    textTitre->setGeometry( QRect( 150, 12, 450, 38 ) );
    QFont textTitre_font(  textTitre->font() );
    textTitre_font.setFamily( "Helvetica [Adobe]" );
    textTitre_font.setPointSize( 24 );
    textTitre->setFont( textTitre_font ); 

    textCodePostal = new QLabel( this, "textCodePostal" );
    textCodePostal->setGeometry( QRect( 110, 60, 100, 20 ) );

    lineCodePostal = new QLineEdit( this, "lineCodePostal" );
    lineCodePostal->setGeometry( QRect( 220, 60, 104, 20 ) );

    ButtonRechercher = new QPushButton( this, "ButtonRechercher" );
    ButtonRechercher->setGeometry( QRect( 390, 60, 120, 20 ) );
    ButtonRechercher->setAutoDefault( FALSE );

    lineVille = new QLineEdit( this, "lineVille" );
    lineVille->setGeometry( QRect( 220, 90, 104, 20 ) );

    ButtonEffacer = new QPushButton( this, "ButtonEffacer" );
    ButtonEffacer->setGeometry( QRect( 390, 90, 120, 20 ) );
    ButtonEffacer->setAutoDefault( FALSE );

    ButtonPrecedent = new QPushButton( this, "ButtonPrecedent" );
    ButtonPrecedent->setGeometry( QRect( 150, 400, 100, 28 ) );
    ButtonPrecedent->setAutoDefault( FALSE );

    ButtonSuivant = new QPushButton( this, "ButtonSuivant" );
    ButtonSuivant->setGeometry( QRect( 275, 400, 100, 28 ) );
    ButtonSuivant->setAutoDefault( FALSE );

    ButtonTerminer = new QPushButton( this, "ButtonTerminer" );
    ButtonTerminer->setGeometry( QRect( 500, 400, 100, 28 ) );
    ButtonTerminer->setAutoDefault( FALSE );

    textVilleDonnee = new QLabel( this, "textVilleDonnee" );
    textVilleDonnee->setGeometry( QRect( 110, 90, 80, 20 ) );

    textCode = new QLabel( this, "textCode" );
    textCode->setGeometry( QRect( 40, 130, 59, 20 ) );

    textVille = new QLabel( this, "textVille" );
    textVille->setGeometry( QRect( 110, 130, 59, 20 ) );

    textAdresse = new QLabel( this, "textAdresse" );
    textAdresse->setGeometry( QRect( 280, 130, 100, 20 ) );

    textSiteWeb = new QLabel( this, "textSiteWeb" );
    textSiteWeb->setGeometry( QRect( 500, 130, 100, 20 ) );

    lineVilleOk[0] = new QLineEdit( this, "lineVilleOk" );
    lineVilleOk[0]->setGeometry( QRect( 110, 160, 150, 20 ) );

    lineCodeOk[0] = new QLineEdit( this, "lineCodeOk" );
    lineCodeOk[0]->setGeometry( QRect( 40, 160, 50, 20 ) );

    lineAdresseOk[0] = new QLineEdit( this, "lineAdresseOk" );
    lineAdresseOk[0]->setGeometry( QRect( 280, 160, 200, 20 ) );

    lineSiteWebOk[0] = new QLineEdit( this, "lineSiteWebOk" );
    lineSiteWebOk[0]->setGeometry( QRect( 500, 160, 200, 20 ) );

    lineVilleOk[1] = new QLineEdit( this, "lineVilleOk" );
    lineVilleOk[1]->setGeometry( QRect( 110, 200, 150, 20 ) );

    lineCodeOk[1] = new QLineEdit( this, "lineCodeOk" );
    lineCodeOk[1]->setGeometry( QRect( 40, 200, 50, 20 ) );

    lineAdresseOk[1] = new QLineEdit( this, "lineAdresseOk" );
    lineAdresseOk[1]->setGeometry( QRect( 280, 200, 200, 20 ) );

    lineSiteWebOk[1] = new QLineEdit( this, "lineSiteWebOk" );
    lineSiteWebOk[1]->setGeometry( QRect( 500, 200, 200, 20 ) );

    lineVilleOk[2] = new QLineEdit( this, "lineVilleOk" );
    lineVilleOk[2]->setGeometry( QRect( 110, 240, 150, 20 ) );

    lineCodeOk[2] = new QLineEdit( this, "lineCodeOk" );
    lineCodeOk[2]->setGeometry( QRect( 40, 240, 50, 20 ) );

    lineAdresseOk[2] = new QLineEdit( this, "lineAdresseOk" );
    lineAdresseOk[2]->setGeometry( QRect( 280, 240, 200, 20 ) );

    lineSiteWebOk[2] = new QLineEdit( this, "lineSiteWebOk" );
    lineSiteWebOk[2]->setGeometry( QRect( 500, 240, 200, 20 ) );

    lineVilleOk[3] = new QLineEdit( this, "lineVilleOk" );
    lineVilleOk[3]->setGeometry( QRect( 110, 280, 150, 20 ) );

    lineCodeOk[3] = new QLineEdit( this, "lineCodeOk" );
    lineCodeOk[3]->setGeometry( QRect( 40, 280, 50, 20 ) );

    lineAdresseOk[3] = new QLineEdit( this, "lineAdresseOk" );
    lineAdresseOk[3]->setGeometry( QRect( 280, 280, 200, 20 ) );

    lineSiteWebOk[3] = new QLineEdit( this, "lineSiteWebOk" );
    lineSiteWebOk[3]->setGeometry( QRect( 500, 280, 200, 20 ) );

    lineVilleOk[4] = new QLineEdit( this, "lineVilleOk" );
    lineVilleOk[4]->setGeometry( QRect( 110, 320, 150, 20 ) );

    lineCodeOk[4] = new QLineEdit( this, "lineCodeOk" );
    lineCodeOk[4]->setGeometry( QRect( 40, 320, 50, 20 ) );

    lineAdresseOk[4] = new QLineEdit( this, "lineAdresseOk" );
    lineAdresseOk[4]->setGeometry( QRect( 280, 320, 200, 20 ) );

    lineSiteWebOk[4] = new QLineEdit( this, "lineSiteWebOk" );
    lineSiteWebOk[4]->setGeometry( QRect( 500, 320, 200, 20 ) );

    lineInformation = new QLineEdit( this, "lineInformation" );
    lineInformation->setGeometry( QRect( 40, 370, 660, 20 ) );

    languageChange();
    resize( QSize(750, 480).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( ButtonEffacer, SIGNAL( clicked() ), this, SLOT( Effacer() ) );
    connect( ButtonPrecedent, SIGNAL( clicked() ), this, SLOT( ListePrecedent() ) );
    connect( ButtonSuivant, SIGNAL( clicked() ), this, SLOT( ListeSuivant() ) );
    connect( ButtonRechercher, SIGNAL( clicked() ), this, SLOT( RechercheCodePostal() ) );
    connect( ButtonTerminer, SIGNAL( clicked() ), this, SLOT( Terminer() ) );
    connect( lineVille, SIGNAL( returnPressed() ), this, SLOT( RechercheCodePostal() ) );
    connect( lineCodePostal, SIGNAL( returnPressed() ), this, SLOT( RechercheCodePostal() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
RechercheCodesPostaux::~RechercheCodesPostaux()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void RechercheCodesPostaux::languageChange()
{
    setCaption( tr( "Recherche des codes postaux de Belgique" ) );
    textTitre->setText( tr( "Codes Postaux de Belgique" ) );
    textCodePostal->setText( tr( "Code Postal:" ) );
    ButtonEffacer->setText( tr( "Effacer" ) );
    ButtonPrecedent->setText( trUtf8( "\x50\x72\xc3\xa9\x63\xc3\xa9\x64\x65\x6e\x74" ) );
    ButtonSuivant->setText( tr( "Suivant" ) );
    ButtonTerminer->setText( tr( "Terminer" ) );
    ButtonRechercher->setText( tr( "Rechercher" ) );
    textVilleDonnee->setText( tr( "Ville :" ) );
    textCode->setText( tr( "Code:" ) );
    textVille->setText( tr( "Ville:" ) );
    textAdresse->setText( tr( "Adresse:" ) );
    textSiteWeb->setText( tr( "Site Web:" ) );
}

ELEMENTCOMPLET 	Resultat[MAX];
int		Compteur;

void RechercheCodesPostaux::RechercheCodePostal()
{
Trace( "Entree dans RechercheCodePostal():" );
int     	Code,rc;
char    	Buff[255];

Trace("Taille : %d",sizeof(ELEMENTCOMPLET));
Code = atoi(lineCodePostal->text());
Trace("lu = %d",Code);
rc = FIConsultation(F1,&Code,&Resultat,MAX - 1);
Trace("Resultat : code %d    ville : %s ( nombre trouve %d)",Resultat[0].Numero,
Resultat[0].Nom,rc);
if (rc >= MAX)
   { Trace("Trop d'\351l\351ment, affiner votre s\351lection");
     lineInformation->setText("Trop d'\351l\351ment, affiner votre s\351lection");
     return; 
   }
     else 
       { sprintf(Buff,"%d élément(s) trouvé(s).",rc);
         lineInformation->setText(Buff);
       }
Compteur = 1;
while (Compteur <= rc)
   { lineVilleOk[Compteur - 1]->setText(Resultat[Compteur - 1].Nom);
     sprintf(Buff,"%d",Resultat[Compteur - 1].Numero);
     lineCodeOk[Compteur - 1]->setText(Buff);
     lineAdresseOk[Compteur - 1]->setText(Resultat[Compteur - 1].Adresse);
     lineSiteWebOk[Compteur - 1]->setText(Resultat[Compteur - 1].SiteWeb);
     Compteur++;
   }
return;

}

void RechercheCodesPostaux::ListeSuivant()
{
    qWarning( "RechercheCodesPostaux::ListeSuivant(): Not implemented yet" );
}

void RechercheCodesPostaux::ListePrecedent()
{
    qWarning( "RechercheCodesPostaux::ListePrecedent(): Not implemented yet" );
}

void RechercheCodesPostaux::Terminer()
{
    qWarning( "RechercheCodesPostaux::Terminer(): Not implemented yet" );
}

void RechercheCodesPostaux::Effacer()
{
    qWarning( "RechercheCodesPostaux::Effacer(): Not implemented yet" );
}

