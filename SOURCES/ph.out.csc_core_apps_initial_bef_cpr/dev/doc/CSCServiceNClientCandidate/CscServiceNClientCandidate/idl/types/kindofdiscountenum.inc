#ifndef GUARD_KINDOFDISCOUNT_ENUM_H
#define GUARD_KINDOFDISCOUNT_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumerate the kinds of discount, e.g. a percentage, or natural, etc.      */
/*----------------------------------------------------------------------------*/
enum KindOfDiscountEnum
{
    Undefined            = 0,
    DiscountInPercent    = 1,      // RABATT_IN_PROCENT  
    RebateInKind         = 2,      // NATURALRABATT
    FixedPrice           = 3,      // FIXPREIS
    FixedDiscountAmount  = 4,      // FIXER RABATTBETRAG
    LogisticsSurcharge   = 5,      // LOGISTIKZUSCHLAG
    Fee                  = 6      // GEBUEHR
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_KINDOFDISCOUNT_ENUM_H
