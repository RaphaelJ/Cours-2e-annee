#include "PremierExemple.h"
#include <qapplication.h>

int main(int argc, char *argv[])
{
QApplication appl(argc,argv);

PremierExemple     F1;
F1.show();

return appl.exec();
}

