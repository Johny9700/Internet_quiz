/****************************************************************************
** Meta object code from reading C++ file 'quizwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../client_app/quizwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quizwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QuizWindow_t {
    QByteArrayData data[14];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QuizWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QuizWindow_t qt_meta_stringdata_QuizWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "QuizWindow"
QT_MOC_LITERAL(1, 11, 24), // "on_connectButton_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 22), // "on_APushButton_clicked"
QT_MOC_LITERAL(4, 60, 22), // "on_BPushButton_clicked"
QT_MOC_LITERAL(5, 83, 22), // "on_CPushButton_clicked"
QT_MOC_LITERAL(6, 106, 22), // "on_DPushButton_clicked"
QT_MOC_LITERAL(7, 129, 25), // "on_exitPushButton_clicked"
QT_MOC_LITERAL(8, 155, 17), // "connectedToServer"
QT_MOC_LITERAL(9, 173, 4), // "read"
QT_MOC_LITERAL(10, 178, 12), // "displayError"
QT_MOC_LITERAL(11, 191, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(12, 220, 11), // "socketError"
QT_MOC_LITERAL(13, 232, 22) // "disconnectedFromServer"

    },
    "QuizWindow\0on_connectButton_clicked\0"
    "\0on_APushButton_clicked\0on_BPushButton_clicked\0"
    "on_CPushButton_clicked\0on_DPushButton_clicked\0"
    "on_exitPushButton_clicked\0connectedToServer\0"
    "read\0displayError\0QAbstractSocket::SocketError\0"
    "socketError\0disconnectedFromServer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QuizWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    1,   72,    2, 0x08 /* Private */,
      13,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void QuizWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QuizWindow *_t = static_cast<QuizWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_connectButton_clicked(); break;
        case 1: _t->on_APushButton_clicked(); break;
        case 2: _t->on_BPushButton_clicked(); break;
        case 3: _t->on_CPushButton_clicked(); break;
        case 4: _t->on_DPushButton_clicked(); break;
        case 5: _t->on_exitPushButton_clicked(); break;
        case 6: _t->connectedToServer(); break;
        case 7: _t->read(); break;
        case 8: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 9: _t->disconnectedFromServer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject QuizWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QuizWindow.data,
      qt_meta_data_QuizWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QuizWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QuizWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QuizWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QuizWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
