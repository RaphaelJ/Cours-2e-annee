#/usr/local/qt/bin/uic FenetreSaisie.ui -o FenetreSaisie.h
#/usr/local/qt/bin/uic FenetreSaisie.ui -i FenetreSaisie.h -o FenetreSaisie.cpp
echo creation de FenetreSaisie.o
g++ -c FenetreSaisie.cpp -I /usr/local/qt/include
#/usr/local/qt/bin/moc FenetreSaisie.h -o moc_FenetreSaisie.cpp
g++ -c moc_FenetreSaisie.cpp -I /usr/local/qt/include
echo creation de FonctionUtile.O
g++ -c FonctionUtile.cpp -D SUN
echo creation de QtDossier2009
g++ -I /usr/local/qt/include -I /usrlocal/qt/mkspec/default -o QtDossier2009 Main.cpp FenetreSaisie.o moc_FenetreSaisie.o FonctionUtile.o -lqt
echo creation de FichierIndex.o
g++ -c FichierIndex.cpp 
echo Creation de Serveur
g++ -o Serveur Serveur.cpp FichierIndex.o FonctionUtile.o
echo creation de AccesFichier
g++ -o AccesFichier AccesFichier.cpp FonctionUtile.o FichierIndex.o
