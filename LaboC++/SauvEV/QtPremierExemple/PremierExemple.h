/****************************************************************************
** Form interface generated from reading ui file 'PremierExemple.ui'
**
** Created: Tue Aug 25 23:06:33 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef PREMIEREXEMPLE_H
#define PREMIEREXEMPLE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLineEdit;
class QLabel;

class PremierExemple : public QDialog
{
    Q_OBJECT

public:
    PremierExemple( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~PremierExemple();

    QPushButton* ButtonSoustraction;
    QPushButton* ButtonMultiplication;
    QPushButton* ButtonDivisionEntiere;
    QLineEdit* editSecondNombre;
    QLineEdit* editResultat;
    QPushButton* ButtonAddition;
    QPushButton* ButtonEffacer;
    QPushButton* ButtonTerminer;
    QLabel* textPremierNombre;
    QLabel* textSecondNombre;
    QLineEdit* editPremierNombre;
    QLabel* textResultat;

public slots:
    virtual void Addition();
    virtual void Soustraction();
    virtual void Multiplication();
    virtual void DivisionEntiere();
    virtual void Effacer();
    virtual void Terminer();

protected:

protected slots:
    virtual void languageChange();

};

#endif // PREMIEREXEMPLE_H
