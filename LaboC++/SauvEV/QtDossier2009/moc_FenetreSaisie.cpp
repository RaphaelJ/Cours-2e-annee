/****************************************************************************
** FenetreSaisie meta object code from reading C++ file 'FenetreSaisie.h'
**
** Created: Tue Nov 3 23:35:44 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "FenetreSaisie.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *FenetreSaisie::className() const
{
    return "FenetreSaisie";
}

QMetaObject *FenetreSaisie::metaObj = 0;
static QMetaObjectCleanUp cleanUp_FenetreSaisie( "FenetreSaisie", &FenetreSaisie::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString FenetreSaisie::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FenetreSaisie", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString FenetreSaisie::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FenetreSaisie", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* FenetreSaisie::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"Login", 0, 0 };
    static const QUMethod slot_1 = {"Terminer", 0, 0 };
    static const QUMethod slot_2 = {"Reservation", 0, 0 };
    static const QUMethod slot_3 = {"SelectionnerOk0", 0, 0 };
    static const QUMethod slot_4 = {"SelectionnerOk1", 0, 0 };
    static const QUMethod slot_5 = {"SelectionnerOk2", 0, 0 };
    static const QUMethod slot_6 = {"SelectionnerOk3", 0, 0 };
    static const QUMethod slot_7 = {"SelectionnerOk4", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"SelectionnerOk", 1, param_slot_8 };
    static const QUMethod slot_9 = {"Precedent", 0, 0 };
    static const QUMethod slot_10 = {"Suivant", 0, 0 };
    static const QUMethod slot_11 = {"Effacer", 0, 0 };
    static const QUMethod slot_12 = {"Recherche", 0, 0 };
    static const QUMethod slot_13 = {"Rendu0", 0, 0 };
    static const QUMethod slot_14 = {"Rendu1", 0, 0 };
    static const QUMethod slot_15 = {"Rendu2", 0, 0 };
    static const QUParameter param_slot_16[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_16 = {"Rendu", 1, param_slot_16 };
    static const QUMethod slot_17 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "Login()", &slot_0, QMetaData::Public },
	{ "Terminer()", &slot_1, QMetaData::Public },
	{ "Reservation()", &slot_2, QMetaData::Public },
	{ "SelectionnerOk0()", &slot_3, QMetaData::Public },
	{ "SelectionnerOk1()", &slot_4, QMetaData::Public },
	{ "SelectionnerOk2()", &slot_5, QMetaData::Public },
	{ "SelectionnerOk3()", &slot_6, QMetaData::Public },
	{ "SelectionnerOk4()", &slot_7, QMetaData::Public },
	{ "SelectionnerOk(int)", &slot_8, QMetaData::Public },
	{ "Precedent()", &slot_9, QMetaData::Public },
	{ "Suivant()", &slot_10, QMetaData::Public },
	{ "Effacer()", &slot_11, QMetaData::Public },
	{ "Recherche()", &slot_12, QMetaData::Public },
	{ "Rendu0()", &slot_13, QMetaData::Public },
	{ "Rendu1()", &slot_14, QMetaData::Public },
	{ "Rendu2()", &slot_15, QMetaData::Public },
	{ "Rendu(int)", &slot_16, QMetaData::Public },
	{ "languageChange()", &slot_17, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"FenetreSaisie", parentObject,
	slot_tbl, 18,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_FenetreSaisie.setMetaObject( metaObj );
    return metaObj;
}

void* FenetreSaisie::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "FenetreSaisie" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool FenetreSaisie::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: Login(); break;
    case 1: Terminer(); break;
    case 2: Reservation(); break;
    case 3: SelectionnerOk0(); break;
    case 4: SelectionnerOk1(); break;
    case 5: SelectionnerOk2(); break;
    case 6: SelectionnerOk3(); break;
    case 7: SelectionnerOk4(); break;
    case 8: SelectionnerOk((int)static_QUType_int.get(_o+1)); break;
    case 9: Precedent(); break;
    case 10: Suivant(); break;
    case 11: Effacer(); break;
    case 12: Recherche(); break;
    case 13: Rendu0(); break;
    case 14: Rendu1(); break;
    case 15: Rendu2(); break;
    case 16: Rendu((int)static_QUType_int.get(_o+1)); break;
    case 17: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool FenetreSaisie::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool FenetreSaisie::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool FenetreSaisie::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
