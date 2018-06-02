/****************************************************************************
** Meta object code from reading C++ file 'maingui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../maingui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maingui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainGUI_t {
    QByteArrayData data[13];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainGUI_t qt_meta_stringdata_MainGUI = {
    {
QT_MOC_LITERAL(0, 0, 7), // "MainGUI"
QT_MOC_LITERAL(1, 8, 17), // "onBnUpdateClicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 18), // "onCBVisibleClicked"
QT_MOC_LITERAL(4, 46, 7), // "checked"
QT_MOC_LITERAL(5, 54, 15), // "selectCellColor"
QT_MOC_LITERAL(6, 70, 16), // "onCellClickEvent"
QT_MOC_LITERAL(7, 87, 13), // "TrackLblCell*"
QT_MOC_LITERAL(8, 101, 4), // "cell"
QT_MOC_LITERAL(9, 106, 15), // "onSelGradPt1btn"
QT_MOC_LITERAL(10, 122, 15), // "onSelGradPt2btn"
QT_MOC_LITERAL(11, 138, 15), // "onGradBnClicked"
QT_MOC_LITERAL(12, 154, 15) // "onSaveBnClicked"

    },
    "MainGUI\0onBnUpdateClicked\0\0"
    "onCBVisibleClicked\0checked\0selectCellColor\0"
    "onCellClickEvent\0TrackLblCell*\0cell\0"
    "onSelGradPt1btn\0onSelGradPt2btn\0"
    "onGradBnClicked\0onSaveBnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    1,   55,    2, 0x0a /* Public */,
       5,    0,   58,    2, 0x0a /* Public */,
       6,    1,   59,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,
      11,    0,   64,    2, 0x0a /* Public */,
      12,    0,   65,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainGUI *_t = static_cast<MainGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onBnUpdateClicked(); break;
        case 1: _t->onCBVisibleClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->selectCellColor(); break;
        case 3: _t->onCellClickEvent((*reinterpret_cast< TrackLblCell*(*)>(_a[1]))); break;
        case 4: _t->onSelGradPt1btn(); break;
        case 5: _t->onSelGradPt2btn(); break;
        case 6: _t->onGradBnClicked(); break;
        case 7: _t->onSaveBnClicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainGUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainGUI.data,
      qt_meta_data_MainGUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainGUI.stringdata0))
        return static_cast<void*>(const_cast< MainGUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
