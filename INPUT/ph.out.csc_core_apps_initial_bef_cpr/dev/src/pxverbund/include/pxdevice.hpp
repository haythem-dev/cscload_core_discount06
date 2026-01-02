/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXDEVICE.HPP
Device class definitions.

REVISION HISTORY

30 Aug 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/

#ifndef PXDEVICE_INC
#define PXDEVICE_INC

#include <string.hpp>
#include "pxdevicetypeenum.hpp"

inline bool  IsVideo(pxDeviceType t)
             {return  (t == pxDVC_VIDEO_WORKSTATION)
                   || (t == pxDVC_VIDEO_TERMINAL)
                   || (t == pxDVC_VIDEO);
             }

inline bool  IsDCT(pxDeviceType t)
             {return  (t == pxDVC_DCT_SERIAL)
                   || (t == pxDVC_DCT_PARALLEL)
                   || (t == pxDVC_DCT);
             }


inline bool  IsFILE(pxDeviceType t)
             {return  (t == pxDVC_FILE);}


inline bool  IsValidDevice(pxDeviceType t)
             {return  (t > pxDVC_UNDEFINED && t <= pxDVC_FILE); }

class pxDevice
{
public:
    virtual           ~pxDevice();
                      pxDevice();       // default constructor
                      pxDevice(const nString& GeraetName,
                               const pxDeviceType GeraetTyp = pxDVC_VIDEO_WORKSTATION);

//  Settings:
    int               Name(const nString& name);
    void              Type(const pxDeviceType t);
    int               Description(const nString& d);

//  Queries:
    const nString&    Name() const      {return GeraetName_;}
    pxDeviceType      Type() const      {return GeraetTyp_;}
    const nString&    Description() const
                                        {return Bezeichnung_;}
                      operator int   () {return GeraetTyp_;}
                      operator short () {return (short) GeraetTyp_;}
    bool              IsVideo() const   { return ::IsVideo(GeraetTyp_);}
    bool              IsDCT  () const   { return ::IsDCT  (GeraetTyp_);}
    bool              IsFILE () const   { return ::IsFILE  (GeraetTyp_);}

private:
    void              Init();

    nString           GeraetName_;      // Device identifier (key)
    pxDeviceType      GeraetTyp_;       // The type
    nString           Bezeichnung_;
};

#endif
