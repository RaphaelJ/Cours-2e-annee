/****************************************************************************
** BorneReservation meta object code from reading C++ file 'BorneReservation.h'
**
** Created: Tue Oct 26 10:06:20 2010
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "BorneReservation.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *BorneReservation::className() const
{
    return "BorneReservation";
}

QMetaObject *BorneReservation::metaObj = 0;
static QMetaObjectCleanUp cleanUp_BorneReservation( "BorneReservation", &BorneReservation::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString BorneReservation::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "BorneReservation", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString BorneReservation::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "BorneReservation", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* BorneReservation::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"Selectionner", 0, 0 };
    static const QUMethod slot_1 = {"Confirmer", 0, 0 };
    static const QUMethod slot_2 = {"Annuler", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"AffichageMenu", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"AffichagePublicite", 1, param_slot_4 };
    static const QUMethod slot_5 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "Selectionner()", &slot_0, QMetaData::Public },
	{ "Confirmer()", &slot_1, QMetaData::Public },
	{ "Annuler()", &slot_2, QMetaData::Public },
	{ "AffichageMenu(const char*)", &slot_3, QMetaData::Public },
	{ "AffichagePublicite(const char*)", &slot_4, QMetaData::Public },
	{ "languageChange()", &slot_5, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"BorneReservation", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_BorneReservation.setMetaObject( metaObj );
    return metaObj;
}

void* BorneReservation::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "BorneReservation" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool BorneReservation::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: Selectionner(); break;
    case 1: Confirmer(); break;
    case 2: Annuler(); break;
    case 3: AffichageMenu((const char*)static_QUType_charstar.get(_o+1)); break;
    case 4: AffichagePublicite((const char*)static_QUType_charstar.get(_o+1)); break;
    case 5: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool BorneReservation::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool BorneReservation::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool BorneReservation::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
