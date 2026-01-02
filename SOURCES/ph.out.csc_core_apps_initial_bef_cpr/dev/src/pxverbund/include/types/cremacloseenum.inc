#ifndef GUARD_CREMACLOSE_ENUM_H
#define GUARD_CREMACLOSE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumeration for crema email types.                                       */
/*----------------------------------------------------------------------------*/
enum CremaCloseEnum
{
    CloseOrder = 0,
    CancelOrder = 1
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_CREMACLOSE_ENUM_H
