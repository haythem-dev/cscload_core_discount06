#ifndef GUARD_ORIGINTYPE_ENUM_H
#define GUARD_ORIGINTYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumeration of origintypes                                                */
/*  check ORIGINNAMES array in oclparam.cpp                                   */
/*----------------------------------------------------------------------------*/
enum OriginTypeEnum
{
    cORTYPE_UNKNOWN = 0,                  //
    cORTYPE_AUXILIARY,                    // type IBT shuttle order                        1   ==> VB
    cORTYPE_CLEARING,                     // type clearing                                 2   ==> CL
    cORTYPE_INSTALLER,                    // type stock installer                          3   ==> ER
    cORTYPE_STOCK,                        // type stock                                    4   ==> LA
    cORTYPE_STOCK_DISTRIBUTION,           // type stock distibution                        5   ==> LV
    cORTYPE_INDUSTRIAL_RETURN,            // type industrial return                        6   ==> IR
    cORTYPE_PARENT_COMPANY,               // type parent company                           7   ==> SH
    cORTYPE_KOMMI_ERROR,                  // type kommi errror                             8   ==> KF
    cORTYPE_TRANSFER,                     // type ueberweiser = UE                         9   ==> UE
    cORTYPE_PIN,                          // type pin order                                10  ==> PI
    cORTYPE_BATCH_TRANSFER,               // type ueberweiser aus Batch = UW               11  ==> UW
    cORTYPE_GLOBUS_ORDER,                 // type Globus Order = GO                        12  ==> GO
    cORTYPE_EDIFAC_ORDER,                 // type Edifac Order = ES                        13  ==> ES
    cORTYPE_FR_CUSTOMER_ORDER,            // type French Prewhole Customer Order    = CO   14  ==> CO
    cORTYPE_FR_INDUSTRIAL_RETURN,         // type French Prewhole Industrial Return = RI   15  ==> RI
    cORTYPE_BATCH_CALLBACK,               // type Batch Callback (Chargenrueckrufe) = BC   16  ==> BC
    cORTYPE_DIRECT_CLOSURE,               // type with direct order close = DC             17  ==> DC
    cORTYPE_IBT_EXCHANGE,                 // type Verbundumlistungen = VU                  18  ==> VU
	cORTYPE_CANCEL_CREMA_ORDER,           // type cancel CREMA orders                      19  ==> CC
    cORTYPE_PURE_IBT_ORDER                // type IBT lines splitted in AnnA context       20  ==> IT
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_ORIGINTYPE_ENUM_H
