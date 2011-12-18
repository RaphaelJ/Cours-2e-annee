/****************************************************************************
** PremierExemple meta object code from reading C++ file 'PremierExemple.h'
**
** Created: Tue Sep 22 13:02:41 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "PremierExemple.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *PremierExemple::className() const
{
    return "PremierExemple";
}

QMetaObject *PremierExemple::metaObj = 0;
static QMetaObjectCleanUp cleanUp_PremierExemple( "PremierExemple", &PremierExemple::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString PremierExemple::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PremierExemple", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString PremierExemple::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PremierExemple", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* PremierExemple::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"Addition", 0, 0 };
    static const QUMethod slot_1 = {"Soustraction", 0, 0 };
    static const QUMethod slot_2 = {"Multiplication", 0, 0 };
    static const QUMethod slot_3 = {"DivisionEntiere", 0, 0 };
    static const QUMethod slot_4 = {"Effacer", 0, 0 };
    static const QUMethod slot_5 = {"Terminer", 0, 0 };
    static const QUMethod slot_6 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "Addition()", &slot_0, QMetaData::Public },
	{ "Soustraction()", &slot_1, QMetaData::Public },
	{ "Multiplication()", &slot_2, QMetaData::Public },
	{ "DivisionEntiere()", &slot_3, QMetaData::Public },
	{ "Effacer()", &slot_4, QMetaData::Public },
	{ "Terminer()", &slot_5, QMetaData::Public },
	{ "languageChange()", &slot_6, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"PremierExemple", parentObject,
	slot_tbl, 7,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_PremierExemple.setMetaObject( metaObj );
    return metaObj;
}

void* PremierExemple::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "PremierExemple" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool PremierExemple::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: Addition(); break;
    case 1: Soustraction(); break;
    case 2: Multiplication(); break;
    case 3: DivisionEntiere(); break;
    case 4: Effacer(); break;
    case 5: Terminer(); break;
    case 6: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool PremierExemple::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool PremierExemple::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool PremierExemple::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
