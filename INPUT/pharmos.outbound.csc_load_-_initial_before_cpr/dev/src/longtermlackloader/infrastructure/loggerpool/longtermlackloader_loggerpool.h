//----------------------------------------------------------------------------
/*! \file
 *  \brief  pool for logger objects in LONGTERMLACKLOADER
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------

#ifndef GUARD_LONGTERMLACKLOADER_LOGGERPOOL_H
#define GUARD_LONGTERMLACKLOADER_LOGGERPOOL_H

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
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

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
	namespace infrastructure
    {
		class LoggerPool
		{
			public:
				static const log4cplus::Logger&    getLoggerLongTermLackLoader();
				static const log4cplus::Logger&    getLoggerViewConn();
				static const log4cplus::Logger&    getLoggerUseCases();
				static const log4cplus::Logger&    getLoggerDomModules();
				static const log4cplus::Logger&    getLoggerDebugOutput();
		};
	}
}

#endif
