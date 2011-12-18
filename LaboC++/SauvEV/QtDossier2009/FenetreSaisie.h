/****************************************************************************
** Form interface generated from reading ui file 'FenetreSaisie.ui'
**
** Created: Sun Nov 1 13:57:59 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FENETRESAISIE_H
#define FENETRESAISIE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;

class FenetreSaisie : public QDialog
{
    Q_OBJECT

public:
    FenetreSaisie( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~FenetreSaisie();

    QLabel* textTitre;
    QLabel* textNom;
    QLineEdit* lineSaisieNom;
    QPushButton* ButtonLogin;
    QPushButton* ButtonReservation;
    QLineEdit* lineNom[3];
    QPushButton* ButtonPrecedent;
    QPushButton* ButtonEffacer;
    QPushButton* ButtonSuivant;
    QLineEdit* lineRecherche;
    QLineEdit* lineNomOk[5];
    QLineEdit* linePrenomOk[5];
    QLineEdit* lineTitreOk[5];
    QLineEdit* lineReserveOk[5];
    QLineEdit* linePrenom[3];
    QLineEdit* lineTitre[3];
    QPushButton* ButtonRendu[3];
    QPushButton* ButtonSelectionnerOk[5];
    QPushButton* ButtonTerminer;
    QLabel* textSaisie;
    QTextEdit* textMessage;
    QLabel* textInformation;
    QLabel* textSelection;

public slots:
    virtual void Login();
    virtual void Terminer();
    virtual void Reservation();
    virtual void SelectionnerOk0();
    virtual void SelectionnerOk1();
    virtual void SelectionnerOk2();
    virtual void SelectionnerOk3();
    virtual void SelectionnerOk4();
    virtual void SelectionnerOk(int);
    virtual void Precedent();
    virtual void Suivant();
    virtual void Effacer();
    virtual void Recherche();
    virtual void Rendu0();
    virtual void Rendu1();
    virtual void Rendu2();
    virtual void Rendu(int);

protected:

protected slots:
    virtual void languageChange();

};

#endif // FENETRESAISIE_H
