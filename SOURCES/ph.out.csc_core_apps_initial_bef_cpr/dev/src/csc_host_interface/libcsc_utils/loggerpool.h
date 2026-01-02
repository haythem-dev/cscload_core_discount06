//---------------------------------------------------------------------------//
/*! \file   
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       23.12.2010
 *  \version    00.00.00.01 first version
 */ //-----------------------------------------------------------------------//

#ifndef GUARD_UTIL_LOGGERPOOL_H
#define GUARD_UTIL_LOGGERPOOL_H

//---------------------------------------------------------------------------//
// forward declaration section 
//---------------------------------------------------------------------------//
namespace log4cplus 
{
  class Logger;
}

namespace basar
{
    namespace cmnutil
    {
        class Logging;
    }
}

//---------------------------------------------------------------------------//
// class definition section
//---------------------------------------------------------------------------//
namespace libcsc_utils
{
    class LoggerPool
    {
        public:	
	        static log4cplus::Logger LoggerCSC;
    };
} // end namespace util



#endif // GUARD_UTIL_LOGGERPOOL_H
