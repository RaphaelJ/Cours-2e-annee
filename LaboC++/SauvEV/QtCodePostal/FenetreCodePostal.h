/****************************************************************************
** Form interface generated from reading ui file 'FenetreCodePostal.ui'
**
** Created: Thu Oct 8 05:18:01 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef RECHERCHECODESPOSTAUX_H
#define RECHERCHECODESPOSTAUX_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class QLineEdit;

class RechercheCodesPostaux : public QDialog
{
    Q_OBJECT

public:
    RechercheCodesPostaux( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~RechercheCodesPostaux();

    QLabel* textTitre;
    QLabel* textCodePostal;
    QPushButton* ButtonEffacer;
    QPushButton* ButtonPrecedent;
    QPushButton* ButtonSuivant;
    QPushButton* ButtonTerminer;
    QPushButton* ButtonRechercher;
    QLabel* textVilleDonnee;
    QLabel* textCode;
    QLabel* textVille;
    QLabel* textAdresse;
    QLabel* textSiteWeb;
    QLineEdit* lineCodeOk[5];
    QLineEdit* lineVilleOk[5];
    QLineEdit* lineAdresseOk[5];
    QLineEdit* lineSiteWebOk[5];
    QLineEdit* lineInformation;
    QLineEdit* lineVille;
    QLineEdit* lineCodePostal;

public slots:
    virtual void RechercheCodePostal();
    virtual void ListeSuivant();
    virtual void ListePrecedent();
    virtual void Terminer();
    virtual void Effacer();

protected:

protected slots:
    virtual void languageChange();

};

#endif // RECHERCHECODESPOSTAUX_H
