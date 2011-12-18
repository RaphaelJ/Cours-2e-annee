#/usr/local/qt/bin/uic FenetreCodePostal.ui -o FenetreCodePostal.h
#/usr/local/qt/bin/uic FenetreCodePostal.ui -i FenetreCodePostal.h -o FenetreCodePostal.cpp
echo FichierIndex.o
g++ -c FichierIndex.cpp
echo Creation de FonctionUtile.o
g++ -c FonctionUtile.cpp -D SUN
echo FenetreCodePostal.o
g++ -c FenetreCodePostal.cpp -I /usr/local/qt/include -D SUN
/usr/local/qt/bin/moc FenetreCodePostal.h -o moc_FenetreCodePostal.cpp
echo moc_FenetreCodePostal.o
g++ -c moc_FenetreCodePostal.cpp -I /usr/local/qt/include
echo Prog
g++ -I /usr/local/qt/include -I /usrlocal/qt/mkspec/default -o Prog Main.cpp FenetreCodePostal.o FichierIndex.o moc_FenetreCodePostal.o FonctionUtile.o -lqt -D SUN
