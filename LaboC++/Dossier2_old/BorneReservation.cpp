/****************************************************************************
** Form implementation generated from reading ui file 'BorneReservation.ui'
**
** Created: mar. oct. 26 10:06:14 2010
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "BorneReservation.h"

#include "Defines.h"
#include "Ecran.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

extern int IdQueue;

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
BorneReservation::BorneReservation(QWidget * parent, const char *name,
				   bool modal, WFlags fl)
:QDialog(parent, name, modal, fl)
{
    if (!name)
	setName("BorneReservation");
    setMinimumSize(QSize(0, 0));
    setMaximumSize(QSize(1200, 600));

    textPub = new QTextEdit(this, "textPub");
    textPub->setGeometry(QRect(20, 20, 760, 90));
    textPub->setReadOnly(TRUE);

    textMenu = new QTextEdit(this, "textMenu");
    textMenu->setGeometry(QRect(20, 150, 480, 100));
    textMenu->setReadOnly(TRUE);

    textChoix = new QLabel(this, "textChoix");
    textChoix->setGeometry(QRect(520, 150, 180, 20));

    lineChoix = new QLineEdit(this, "lineChoix");
    lineChoix->setGeometry(QRect(660, 150, 120, 21));

    ButtonSelectionner = new QPushButton(this, "ButtonSelectionner");
    ButtonSelectionner->setGeometry(QRect(520, 210, 120, 29));
    ButtonSelectionner->setAutoDefault(FALSE);

    ButtonAnnuler = new QPushButton(this, "ButtonAnnuler");
    ButtonAnnuler->setGeometry(QRect(260, 330, 100, 29));
    ButtonAnnuler->setAutoRepeat(FALSE);
    ButtonAnnuler->setAutoDefault(FALSE);

    ButtonConfirmer = new QPushButton(this, "ButtonConfirmer");
    ButtonConfirmer->setGeometry(QRect(100, 330, 100, 29));
    ButtonConfirmer->setAutoDefault(FALSE);

    textNbPlaces = new QLabel(this, "textNbPlaces");
    textNbPlaces->setGeometry(QRect(520, 180, 180, 20));

    lineNbPlaces = new QLineEdit(this, "lineNbPlaces");
    lineNbPlaces->setGeometry(QRect(720, 180, 60, 20));
    languageChange();
    resize(QSize(800, 400).expandedTo(minimumSizeHint()));
    clearWState(WState_Polished);

    // signals and slots connections
    connect(ButtonAnnuler, SIGNAL(pressed()), this, SLOT(Annuler()));
    connect(ButtonConfirmer, SIGNAL(pressed()), this, SLOT(Confirmer()));
    connect(ButtonSelectionner, SIGNAL(pressed()), this,
	    SLOT(Selectionner()));
    connect(lineChoix, SIGNAL(returnPressed()), this,
	    SLOT(Selectionner()));
    connect(lineNbPlaces, SIGNAL(returnPressed()), this,
	    SLOT(Selectionner()));

    AffichagePublicite("Chargement en cours ...");
    AffichageMenu("Chargement en cours ...");
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
    setCaption(tr("Borne Reservation"));
    textChoix->setText(tr("Votre choix:"));
    ButtonSelectionner->setText(tr("Selectionner"));
    ButtonAnnuler->setText(tr("Annuler"));
    ButtonConfirmer->setText(tr("Confirmer"));
    textNbPlaces->setText(tr("Nombre de places:"));
}

extern int ProcessReservation;
extern void AfficherMenuPrincipal(int);

void BorneReservation::Selectionner()
{
	Trace("BorneReservation::Selectionner()");
	
	char choixBuff[80];
	char placesBuff[80];
	int choix, nPlaces;
	
	strcpy(choixBuff, lineChoix->text());
	choix = atoi(choixBuff);
	
	strcpy(placesBuff, lineNbPlaces->text());
	nPlaces = atoi(placesBuff);
	
	if (choix) {
		MESSAGE msg;
		msg.sender = getpid();
		
		if (nPlaces <= 0) { // Consultation des événements disponibles d'un type
			MENU menu = { choix, 0 };
			
			// Annule une consultation en cours
			if (ProcessReservation != 0)
				this->Annuler();

			// Demande la liste d'un type d'événement
			msg.dest = SERVER_RECV;
			msg.type = CONSULTER_EVENTS;
			msg.data.menu = menu;
			
			if (msgsnd(IdQueue, &msg, MESSAGE_SIZE, 0) != 0) {
				TraceErreur("Erreur de msgsnd()...");
				exit(1);
			}
			Trace("Message de listage des événements emis\n");
			
			// Reçoit la liste des événements
			if (msgrcv(IdQueue, &msg, MESSAGE_SIZE, getpid(), 0) == -1) {
				TraceErreur("Erreur de msgrcv()...");
				exit(1);
			}
			
			// Affiche la liste des événements
			textMenu->clear();
			
			ProcessReservation = msg.sender;
			
			char buff[1000];
			buff[0] = '\0';
		
			Trace("Evénements reçus de %d", ProcessReservation);
				
			for (int i = 0; i < MAX_EVENTS; i++) {
				if (msg.data.events[i].nom[0] != '\0') {
					char tempBuff[1000];
					
					sprintf(tempBuff, "%2d - %-20s%s %-20s %3d\n",
						i + 1, msg.data.events[i].nom, msg.data.events[i].date,
						msg.data.events[i].localisation, msg.data.events[i].libre);
				
					strcat(buff, tempBuff);
				}
			}
			AffichageMenu(buff);
		} else { // Réservation des places
			Trace("Emission à %d", (int) ProcessReservation);
			
			msg.dest = ProcessReservation;
			msg.type = RESERVATION;
			
			msg.data.menu.choix = choix;
			msg.data.menu.nPlaces = nPlaces;
			
			if (msgsnd(IdQueue, &msg, MESSAGE_SIZE, 0) != 0) {
				TraceErreur("Erreur de msgsnd()...");
				exit(1);
			}
			
			AffichageMenu("En attente de la réponse du serveur ...\n" // FIXME
				      "Cela peut prendre une vingtaine de secondes");
			
			// Valide la réservation
			if (msgrcv(IdQueue, &msg, MESSAGE_SIZE, getpid(), 0) == -1) {
				TraceErreur("Erreur de msgrcv()...");
				exit(1);
			}
			
			
			if (msg.type == OK)
				AffichageMenu("Comfirmez la réservation, vous avez 20 secondes");
			else if (msg.type == STOCK_INSUFFISANT) {
				TraceErreur("Il n'y a plus assez de place pour l'événement");
				
				AfficherMenuPrincipal(0);
			}
		}
	}
}

void BorneReservation::Confirmer()
{
	Trace("BorneReservation::Confirmer()");
	
	MESSAGE msg;
	msg.dest = ProcessReservation;	
	msg.type = RESERVATION;
	msg.sender = getpid();
	
	if (msgsnd(IdQueue, &msg, MESSAGE_SIZE, 0) != 0) {
		TraceErreur("Erreur de msgsnd()...");
		exit(1);
	}
	
	Trace("Réservation envoyée à %d", (int) ProcessReservation);
	
	AfficherMenuPrincipal(0);
}

void BorneReservation::Annuler()
{
	Trace("BorneReservation::Annuler()");
	
	MESSAGE msg;
	msg.dest = ProcessReservation;	
	msg.type = ANNULER;
	msg.sender = getpid();
	
	if (msgsnd(IdQueue, &msg, MESSAGE_SIZE, 0) != 0) {
		TraceErreur("Erreur de msgsnd()...");
		exit(1);
	}
	
	Trace("Annulation envoyée à %d", (int) ProcessReservation);
	
	AfficherMenuPrincipal(0);
}

void BorneReservation::AffichageMenu(const char* M)
{
    Trace("BorneReservation::AffichageMenu(const char*)");
    
    textMenu->setText(M);
    lineChoix->clear();
    lineNbPlaces->clear();
}

void BorneReservation::AffichagePublicite(const char *P)
{
    Trace("BorneReservation::AffichagePublicite(const char*)");
    textPub->setText(P);
}
