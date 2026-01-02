//----------------------------------------------------------------------------
/*! \file   loggerpool.cpp
 *  \brief  pool for logger objects
 *  \author Frank Naumann
 *  \date   25.03.2010
 */
//----------------------------------------------------------------------------

#include "commonheader.h"
#include "loggerpool.h"

//----------------------------------------------------------------------------

namespace zpldcust {

//! \brief get global logging instance for zpldcust
log4cplus::Logger LoggerPool::zpldcust = basar::cmnutil::Logging::getInstance("zpldcust");

//----------------------------------------------------------------------------

} //namespace zpldcust

//----------------------------------------------------------------------------
