#ifndef Oracle_Oracle_INCLUDED
#define Oracle_Oracle_INCLUDED

#include "Poco/Foundation.h"

typedef struct OCI_Resultset OCI_Resultset;
typedef struct OCI_Connection OCI_Connection;
typedef struct OCI_Statement OCI_Statement;
typedef struct OCI_Column OCI_Column;

//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the MySQL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// MySQL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
#if defined(ORACLE_EXPORTS)
#define Oracle_API __declspec(dllexport)
#else
#define Oracle_API __declspec(dllimport)
#endif
#endif


#if !defined(Oracle_API)
#define Oracle_API
#endif


//
// Automatically link Data library.
//
#if defined(_MSC_VER)
#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(ORACLE_EXPORTS)
#pragma comment(lib, "PocoDataOracle" POCO_LIB_SUFFIX)
#endif
#endif

#include "Poco/Data/Oracle/TypeHandler.h"

#endif