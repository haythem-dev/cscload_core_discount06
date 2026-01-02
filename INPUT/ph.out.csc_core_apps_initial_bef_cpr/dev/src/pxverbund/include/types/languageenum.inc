#ifndef GUARD_LANGUAGE_ENUM_H
#define GUARD_LANGUAGE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

enum LanguageEnum
{
	UnknownLanguage = -1,
	German = 0,
	English = 1,
	French = 2,
	Croatian = 3,
	Italian = 4
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_LANGUAGE_ENUM_H
