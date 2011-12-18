/****************************************************************************
** RechercheCodesPostaux meta object code from reading C++ file 'FenetreCodePostal.h'
**
** Created: Mon Oct 5 10:58:49 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "FenetreCodePostal.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *RechercheCodesPostaux::className() const
{
    return "RechercheCodesPostaux";
}

QMetaObject *RechercheCodesPostaux::metaObj = 0;
static QMetaObjectCleanUp cleanUp_RechercheCodesPostaux( "RechercheCodesPostaux", &RechercheCodesPostaux::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString RechercheCodesPostaux::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "RechercheCodesPostaux", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString RechercheCodesPostaux::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "RechercheCodesPostaux", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* RechercheCodesPostaux::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"RechercheCodePostal", 0, 0 };
    static const QUMethod slot_1 = {"ListeSuivant", 0, 0 };
    static const QUMethod slot_2 = {"ListePrecedent", 0, 0 };
    static const QUMethod slot_3 = {"Terminer", 0, 0 };
    static const QUMethod slot_4 = {"Effacer", 0, 0 };
    static const QUMethod slot_5 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "RechercheCodePostal()", &slot_0, QMetaData::Public },
	{ "ListeSuivant()", &slot_1, QMetaData::Public },
	{ "ListePrecedent()", &slot_2, QMetaData::Public },
	{ "Terminer()", &slot_3, QMetaData::Public },
	{ "Effacer()", &slot_4, QMetaData::Public },
	{ "languageChange()", &slot_5, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"RechercheCodesPostaux", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_RechercheCodesPostaux.setMetaObject( metaObj );
    return metaObj;
}

void* RechercheCodesPostaux::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "RechercheCodesPostaux" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool RechercheCodesPostaux::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: RechercheCodePostal(); break;
    case 1: ListeSuivant(); break;
    case 2: ListePrecedent(); break;
    case 3: Terminer(); break;
    case 4: Effacer(); break;
    case 5: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool RechercheCodesPostaux::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool RechercheCodesPostaux::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool RechercheCodesPostaux::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
