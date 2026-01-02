//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientdmexception.cpp
 *  \brief  Exceptions for KSCClientDM.
 *  \author Stefan Will
 *  \date   06.02.2008
 */
//-------------------------------------------------------------------------------------------------//

#include "kscclientdmexception.h"
#include <libbasardbaspect.h>

KSCClientDMException::KSCClientDMException (const basar::cmnutil::ExceptionInfoStruct& sInfo)
  : basar::cmnutil::BasarException (sInfo, "KSCClientDMException")
{
}
