//--------------------------------------------------------------------------------------------------//
/*! \file loggerpool.cpp
 *  \brief pool for logger objects
 *  \author Dirk Kapusta
 *  \date 05.02.2008
 *  \version 00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
using log4cplus::Logger;
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libBatch
{
    Logger LoggerPool::LoggerLibBatch	  = Logging::getInstance( "libBatch"              );
    Logger LoggerPool::LoggerCmdLine      = Logging::getInstance( "libBatch.cmdLine"      );
    Logger LoggerPool::LoggerUserAdmin    = Logging::getInstance( "libBatch.userAdmin"    );
    Logger LoggerPool::LoggerDBConnection = Logging::getInstance( "libBatch.dbConnection" );
    //Logger LoggerPool::LoggerVersion      = Logging::getInstance( "libBatch.version" );
} // end namespace libBatch
