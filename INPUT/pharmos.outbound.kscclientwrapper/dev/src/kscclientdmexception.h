//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientdmexception.h
 *  \brief  Exceptions for KSCClientDM.
 *  \author Stefan Will
 *  \date   06.02.2008
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_KSCCLIENTDMEXCEPTION_H
#define GUARD_KSCCLIENTDMEXCEPTION_H

#include <libbasardbaspect_definitions.h>

//! \brief  Exception class used within KSCClientDM.
class KSCClientDMException : public basar::cmnutil::BasarException
{
  public:
    //! \brief  Constructor.
    KSCClientDMException (const basar::cmnutil::ExceptionInfoStruct& sInfo);
};
#endif
