#include "exceptionhelper.h"

#include <libbasarcmnutil.h>

namespace libcsc
{
	namespace exceptions
	{
		void ExceptionHelper::processAccessorException(
			basar::Exception & e, 
			const log4cplus::Logger & logger,
			basar::ConstString functionName, 
			const basar::VarString & executeMethod, 
			basar::ConstString file, 
			basar::Int32 line 
				)
		{
			basar::VarString msg;
			msg.format( "Function %s: tried to execute access method '%s'(file: %s; line: %i).", 
						functionName, executeMethod.c_str(), file, line );
			logger.forcedLog( log4cplus::ERROR_LOG_LEVEL, msg, file, line );
			e.fillInStackTrace( msg, file, line );
		}

		void ExceptionHelper::processBasarException( basar::Exception & e,  const log4cplus::Logger& logger, basar::ConstString functionName, basar::ConstString file, const basar::Int32 line )
		{
			std::stringstream ss; ss << "Exception caught in '" << functionName << "'!";
			e.fillInStackTrace( ss.str().c_str(), file, line );
			logger.forcedLog( log4cplus::ERROR_LOG_LEVEL, e.stackTrace(), file, line );
		}

	} // end namespace exceptions
} // end namespace libcsc
