/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Implementation of methods for the device base class.

REVISION HISTORY

30 Aug 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/
#include "pxdevice.hpp"

/*----------------------------------------------------------------------------*/
/*  Constructors.                                                             */
/*----------------------------------------------------------------------------*/
pxDevice :: pxDevice                    // the default
(
)
{
    Init();
}

pxDevice :: pxDevice                    // to pass the key values
(
    const nString&     GeraetName,
    const pxDeviceType GeraetTyp
)
{
    Init();
    GeraetName_ = GeraetName;
    GeraetTyp_  = GeraetTyp;
}

/*----------------------------------------------------------------------------*/
/*  Set data members.                                                         */
/*----------------------------------------------------------------------------*/
int
pxDevice :: Name
(
    const nString& name
)
{
    GeraetName_ = name;
    GeraetName_.ToUpper();
    return 0;
}

int
pxDevice :: Description
(
    const nString& d
)
{
    Bezeichnung_ = d;
    return 0;
}

void
pxDevice :: Type
(
    const pxDeviceType t
)
{
    if ( ::IsValidDevice(t) )
    {
        GeraetTyp_ = t;
    }
}

/*----------------------------------------------------------------------------*/
/*  Initialize data members.                                                  */
/*----------------------------------------------------------------------------*/
void
pxDevice :: Init
(
)
{
    GeraetName_ = "UNKNOWN";
    GeraetTyp_ = pxDVC_VIDEO_WORKSTATION;
}


/*----------------------------------------------------------------------------*/
/*  Destruction.                                                              */
/*----------------------------------------------------------------------------*/
pxDevice :: ~pxDevice()
{
}
