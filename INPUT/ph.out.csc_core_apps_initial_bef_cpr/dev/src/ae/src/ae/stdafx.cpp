// stdafx.cpp : source file that includes just the standard includes
//  ae.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#endif

CAeApp* AeGetApp()
{
    return (CAeApp*)AfxGetApp();
}

COrderType& GetOrderType()
{
    return AeGetApp()->GetOrderType();
}

CAeUser& GetAeUser()
{
    return *AeGetApp()->m_pAeUser;
}
