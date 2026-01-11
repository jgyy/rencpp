/****************************************************************************
** Meta object code from reading C++ file 'gameengine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/gameengine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameengine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameEngine_t {
    QByteArrayData data[19];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameEngine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameEngine_t qt_meta_stringdata_GameEngine = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameEngine"
QT_MOC_LITERAL(1, 11, 18), // "currentTextChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "choicesChanged"
QT_MOC_LITERAL(4, 46, 16), // "canGoBackChanged"
QT_MOC_LITERAL(5, 63, 9), // "gameEnded"
QT_MOC_LITERAL(6, 73, 10), // "endingText"
QT_MOC_LITERAL(7, 84, 13), // "errorOccurred"
QT_MOC_LITERAL(8, 98, 5), // "error"
QT_MOC_LITERAL(9, 104, 9), // "loadStory"
QT_MOC_LITERAL(10, 114, 8), // "filePath"
QT_MOC_LITERAL(11, 123, 10), // "makeChoice"
QT_MOC_LITERAL(12, 134, 11), // "choiceIndex"
QT_MOC_LITERAL(13, 146, 6), // "goBack"
QT_MOC_LITERAL(14, 153, 7), // "restart"
QT_MOC_LITERAL(15, 161, 11), // "currentText"
QT_MOC_LITERAL(16, 173, 7), // "choices"
QT_MOC_LITERAL(17, 181, 9), // "canGoBack"
QT_MOC_LITERAL(18, 191, 11) // "isGameEnded"

    },
    "GameEngine\0currentTextChanged\0\0"
    "choicesChanged\0canGoBackChanged\0"
    "gameEnded\0endingText\0errorOccurred\0"
    "error\0loadStory\0filePath\0makeChoice\0"
    "choiceIndex\0goBack\0restart\0currentText\0"
    "choices\0canGoBack\0isGameEnded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameEngine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       4,   76, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       7,    1,   65,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       9,    1,   68,    2, 0x02 /* Public */,
      11,    1,   71,    2, 0x02 /* Public */,
      13,    0,   74,    2, 0x02 /* Public */,
      14,    0,   75,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      15, QMetaType::QString, 0x00495001,
      16, QMetaType::QVariantList, 0x00495001,
      17, QMetaType::Bool, 0x00495001,
      18, QMetaType::Bool, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void GameEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameEngine *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->currentTextChanged(); break;
        case 1: _t->choicesChanged(); break;
        case 2: _t->canGoBackChanged(); break;
        case 3: _t->gameEnded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->loadStory((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->makeChoice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->goBack(); break;
        case 8: _t->restart(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameEngine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameEngine::currentTextChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GameEngine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameEngine::choicesChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GameEngine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameEngine::canGoBackChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GameEngine::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameEngine::gameEnded)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GameEngine::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameEngine::errorOccurred)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GameEngine *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->currentText(); break;
        case 1: *reinterpret_cast< QVariantList*>(_v) = _t->choices(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->canGoBack(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->isGameEnded(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject GameEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GameEngine.data,
    qt_meta_data_GameEngine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameEngine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GameEngine::currentTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GameEngine::choicesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GameEngine::canGoBackChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GameEngine::gameEnded(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GameEngine::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
