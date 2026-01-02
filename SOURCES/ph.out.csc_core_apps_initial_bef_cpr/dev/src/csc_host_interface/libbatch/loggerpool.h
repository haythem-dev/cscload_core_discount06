//--------------------------------------------------------------------------------------------------//
/*! \file       loggerpool.h
 *  \brief      pool for logger objects in libBatch
 *  \author     Dirk Kapusta
 *  \date       05.02.2008
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBBATCH_LOGGERPOOL_H
#define GUARD_LIBBATCH_LOGGERPOOL_H

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace log4cplus
{
  class Logger;
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libBatch
{
    class LoggerPool
    {
        public:	
            static log4cplus::Logger LoggerLibBatch;
            static log4cplus::Logger LoggerCmdLine;
            static log4cplus::Logger LoggerUserAdmin;
            static log4cplus::Logger LoggerDBConnection;
            //static log4cplus::Logger LoggerVersion;
    };

} //namespace libBatch

#endif // GUARD_LIBBATCH_LOGGERPOOL_H
