# /usr/local/qt/bin/uic PremierExemple.ui -o PremierExemple.h
# /usr/local/qt/bin/uic PremierExemple.ui -i PremierExemple.h -o PremierExemple.cpp
g++ -c PremierExemple.cpp -I /usr/local/qt/include
/usr/local/qt/bin/moc PremierExemple.h -o moc_PremierExemple.cpp
g++ -c moc_PremierExemple.cpp -I /usr/local/qt/include
g++ -I /usr/local/qt/include -I /usrlocal/qt/mkspec/default -o Prog Main.cpp PremierExemple.o moc_PremierExemple.o -lqt
