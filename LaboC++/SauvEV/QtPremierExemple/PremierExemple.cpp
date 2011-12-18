/****************************************************************************
** Form implementation generated from reading ui file 'PremierExemple.ui'
**
** Created: Tue Aug 25 23:06:33 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "PremierExemple.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a PremierExemple as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
PremierExemple::PremierExemple( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "PremierExemple" );

    ButtonSoustraction = new QPushButton( this, "ButtonSoustraction" );
    ButtonSoustraction->setGeometry( QRect( 130, 160, 50, 28 ) );
    ButtonSoustraction->setAutoDefault( FALSE );

    ButtonMultiplication = new QPushButton( this, "ButtonMultiplication" );
    ButtonMultiplication->setGeometry( QRect( 210, 160, 50, 28 ) );
    ButtonMultiplication->setAutoDefault( FALSE );

    ButtonDivisionEntiere = new QPushButton( this, "ButtonDivisionEntiere" );
    ButtonDivisionEntiere->setGeometry( QRect( 290, 160, 50, 28 ) );
    ButtonDivisionEntiere->setAutoDefault( FALSE );

    editSecondNombre = new QLineEdit( this, "editSecondNombre" );
    editSecondNombre->setGeometry( QRect( 220, 100, 90, 20 ) );

    editResultat = new QLineEdit( this, "editResultat" );
    editResultat->setGeometry( QRect( 220, 230, 90, 20 ) );

    ButtonAddition = new QPushButton( this, "ButtonAddition" );
    ButtonAddition->setGeometry( QRect( 50, 160, 50, 28 ) );
    ButtonAddition->setAutoDefault( FALSE );

    ButtonEffacer = new QPushButton( this, "ButtonEffacer" );
    ButtonEffacer->setGeometry( QRect( 60, 280, 85, 28 ) );
    ButtonEffacer->setAutoDefault( FALSE );

    ButtonTerminer = new QPushButton( this, "ButtonTerminer" );
    ButtonTerminer->setGeometry( QRect( 310, 280, 85, 28 ) );
    ButtonTerminer->setAutoDefault( FALSE );

    textPremierNombre = new QLabel( this, "textPremierNombre" );
    textPremierNombre->setGeometry( QRect( 50, 50, 110, 20 ) );

    textSecondNombre = new QLabel( this, "textSecondNombre" );
    textSecondNombre->setGeometry( QRect( 50, 100, 160, 20 ) );

    editPremierNombre = new QLineEdit( this, "editPremierNombre" );
    editPremierNombre->setGeometry( QRect( 220, 50, 90, 20 ) );

    textResultat = new QLabel( this, "textResultat" );
    textResultat->setGeometry( QRect( 60, 230, 90, 20 ) );
    languageChange();
    resize( QSize(459, 346).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( ButtonAddition, SIGNAL( clicked() ), this, SLOT( Addition() ) );
    connect( ButtonSoustraction, SIGNAL( clicked() ), this, SLOT( Soustraction() ) );
    connect( ButtonMultiplication, SIGNAL( clicked() ), this, SLOT( Multiplication() ) );
    connect( ButtonDivisionEntiere, SIGNAL( clicked() ), this, SLOT( DivisionEntiere() ) );
    connect( ButtonEffacer, SIGNAL( clicked() ), this, SLOT( Effacer() ) );
    connect( ButtonTerminer, SIGNAL( clicked() ), this, SLOT( Terminer() ) );
    connect( editPremierNombre, SIGNAL( returnPressed() ), editSecondNombre, SLOT( setFocus() ) );

    // tab order
    setTabOrder( editPremierNombre, editSecondNombre );
    setTabOrder( editSecondNombre, ButtonAddition );
    setTabOrder( ButtonAddition, ButtonSoustraction );
    setTabOrder( ButtonSoustraction, ButtonMultiplication );
    setTabOrder( ButtonMultiplication, ButtonDivisionEntiere );
    setTabOrder( ButtonDivisionEntiere, editResultat );
    setTabOrder( editResultat, ButtonEffacer );
    setTabOrder( ButtonEffacer, ButtonTerminer );
}

/*
 *  Destroys the object and frees any allocated resources
 */
PremierExemple::~PremierExemple()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void PremierExemple::languageChange()
{
    setCaption( tr( "Premier Exemple" ) );
    ButtonSoustraction->setText( tr( "-" ) );
    ButtonMultiplication->setText( tr( "*" ) );
    ButtonDivisionEntiere->setText( tr( "/" ) );
    ButtonAddition->setText( tr( "+" ) );
    ButtonEffacer->setText( tr( "Effacer" ) );
    ButtonTerminer->setText( tr( "Terminer" ) );
    textPremierNombre->setText( tr( "Entrer un nombre:" ) );
    textSecondNombre->setText( trUtf8( "\x45\x6e\x74\x72\x65\x72\x20\x75\x6e\x20\x64\x65\x75\x78\x69\xc3\xa8\x6d\x65\x20\x6e\x6f\x6d\x62\x72\x65\x3a" ) );
    textResultat->setText( trUtf8( "\x52\xc3\xa9\x73\x75\x6c\x74\x61\x74\x3a" ) );
}

void PremierExemple::Addition()
{
char    Buff1[5],Buff2[5];
int     i,j,res;

strcpy(Buff1,editPremierNombre->text());
i = atoi(Buff1);
strcpy(Buff2,editSecondNombre->text());
j = atoi(Buff2);
res = i+j;
sprintf(Buff1,"%d",res);

editResultat->setText(Buff1);

    qWarning( "PremierExemple::Addition(): Not implemented yet" );
}

void PremierExemple::Soustraction()
{
    qWarning( "PremierExemple::Soustraction(): Not implemented yet" );
}

void PremierExemple::Multiplication()
{
    qWarning( "PremierExemple::Multiplication(): Not implemented yet" );
}

void PremierExemple::DivisionEntiere()
{
    qWarning( "PremierExemple::DivisionEntiere(): Not implemented yet" );
}

void PremierExemple::Effacer()
{
editPremierNombre->clear();
    qWarning( "PremierExemple::Effacer(): Not implemented yet" );
}

void PremierExemple::Terminer()
{
    qWarning( "PremierExemple::Terminer(): Not implemented yet" );
}

