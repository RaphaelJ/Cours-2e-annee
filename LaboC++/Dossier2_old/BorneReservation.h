/****************************************************************************
** Form interface generated from reading ui file 'BorneReservation.ui'
**
** Created: mar. oct. 26 10:06:09 2010
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef BORNERESERVATION_H
#define BORNERESERVATION_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTextEdit;
class QLabel;
class QLineEdit;
class QPushButton;

class BorneReservation : public QDialog {
  Q_OBJECT public:
    BorneReservation(QWidget * parent = 0, const char *name =
		     0, bool modal = FALSE, WFlags fl = 0);
    ~BorneReservation();

    QTextEdit *textPub;
    QTextEdit *textMenu;
    QLabel *textChoix;
    QLineEdit *lineChoix;
    QPushButton *ButtonSelectionner;
    QPushButton *ButtonAnnuler;
    QPushButton *ButtonConfirmer;
    QLabel *textNbPlaces;
    QLineEdit *lineNbPlaces;

    public slots:virtual void Selectionner();
    virtual void Confirmer();
    virtual void Annuler();
    virtual void AffichageMenu(const char *);
    virtual void AffichagePublicite(const char *);

  protected:

     protected slots:virtual void languageChange();

};

#endif				// BORNERESERVATION_H
