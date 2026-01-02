#ifndef GUARD_PAYMENTSFILTER_ENUM_H
#define GUARD_PAYMENTSFILTER_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumeration for payments filter in payments request.                                       */
/*----------------------------------------------------------------------------*/
enum PaymentsFilterEnum
{
    DelayedDocuments = 0,
    OverdueDocuments = 1,
    AllDocuments = 2
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_PAYMENTSFILTER_ENUM_H
