/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 6.7.1
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // G:/oldDesktop/programing/newS/UNI/402-403-AP/QTFiles/loginPage/build/Desktop_Qt_6_7_1_MinGW_64_bit-Debug/debug/loginPage_en_CA.qm
  0x0,0x0,0x0,0x21,
  0x3c,
  0xb8,0x64,0x18,0xca,0xef,0x9c,0x95,0xcd,0x21,0x1c,0xbf,0x60,0xa1,0xbd,0xdd,0xa7,
  0x0,0x0,0x0,0x5,0x65,0x6e,0x5f,0x43,0x41,0x88,0x0,0x0,0x0,0x2,0x1,0x1,
  
  
};

static const unsigned char qt_resource_name[] = {
  // i18n
  0x0,0x4,
  0x0,0x6,0xc4,0xee,
  0x0,0x69,
  0x0,0x31,0x0,0x38,0x0,0x6e,
    // loginPage_en_CA.qm
  0x0,0x12,
  0x4,0x1b,0xee,0x9d,
  0x0,0x6c,
  0x0,0x6f,0x0,0x67,0x0,0x69,0x0,0x6e,0x0,0x50,0x0,0x61,0x0,0x67,0x0,0x65,0x0,0x5f,0x0,0x65,0x0,0x6e,0x0,0x5f,0x0,0x43,0x0,0x41,0x0,0x2e,0x0,0x71,
  0x0,0x6d,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/i18n
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x2,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/i18n/loginPage_en_CA.qm
  0x0,0x0,0x0,0xe,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x8f,0xcf,0x40,0xe,0xc3,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_qmake_qmake_qm_files)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_qmake_qmake_qm_files)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qmake_qmake_qm_files)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qmake_qmake_qm_files)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

#ifdef __clang__
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_qmake_qmake_qm_files)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qmake_qmake_qm_files)(); }
   } dummy;
}

#ifdef __clang__
#   pragma clang diagnostic pop
#endif
