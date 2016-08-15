#ifndef MYKEY_GLOBAL_H
#define MYKEY_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MYKEY_LIB
# define MYKEY_EXPORT Q_DECL_EXPORT
#else
# define MYKEY_EXPORT Q_DECL_IMPORT
#endif

#endif // MYKEY_GLOBAL_H
