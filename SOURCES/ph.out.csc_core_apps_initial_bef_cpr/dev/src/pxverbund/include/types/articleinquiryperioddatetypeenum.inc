#ifndef GUARD_ARTICLEINQUIRYPERIODDATETYPE_ENUM_H
#define GUARD_ARTICLEINQUIRYPERIODDATETYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumeration for period date types in article inquiry request.                                       */
/*----------------------------------------------------------------------------*/
enum ArticleInquiryPeriodDateTypeEnum
{
    Creation    = 0,
    Change      = 1,
    AllDates    = 2
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_ARTICLEINQUIRYPERIODDATETYPE_ENUM_H
