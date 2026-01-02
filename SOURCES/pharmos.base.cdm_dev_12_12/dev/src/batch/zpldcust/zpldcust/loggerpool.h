//----------------------------------------------------------------------------
/*! \file   loggerpool.h
 *  \brief  pool for logger objects in zpldcust.
 *  \author Frank Naumann
 *  \date   31.03.2010
 */
//----------------------------------------------------------------------------

#ifndef GUARD_ZPLDCUST_LOGGERPOOL_H
#define GUARD_ZPLDCUST_LOGGERPOOL_H

//----------------------------------------------------------------------------

namespace zpldcust {

//---------------------------------------------------------------------------
/*! \brief class for initialized logger objects. final class.
 */
class LoggerPool
{
public:	
  static log4cplus::Logger zpldcust; //!< logger for zpldcust (global)
};

//----------------------------------------------------------------------------

} //namespace zpldcust

//----------------------------------------------------------------------------

#endif // GUARD_ZPLDCUST_LOGGERPOOL_H

//----------------------------------------------------------------------------
