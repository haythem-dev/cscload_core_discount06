#include <libbasarcmnutil.h>
#include "baseexception.h"
#include "exceptionhandler.h"

namespace util
{
void ExceptionHandler::processAccessorException( 
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
	throw;
}

void ExceptionHandler::processBasarException( basar::Exception & e,  const log4cplus::Logger& logger, basar::ConstString functionName, basar::ConstString file, const basar::Int32 line )
{
    std::stringstream ss; ss << "Exception caught in '" << functionName << "'!";
    e.fillInStackTrace( ss.str().c_str(), file, line );
    logger.forcedLog( log4cplus::ERROR_LOG_LEVEL, e.stackTrace(), file, line );
    throw;
}

void ExceptionHandler::processReasonException( util::BaseException& e,  const log4cplus::Logger& logger, basar::ConstString functionName, basar::ConstString file, const basar::Int32 line )
{
    std::stringstream ss; ss << "IRMException caught in '" << functionName << "'!";
    e.fillInStackTrace( ss.str().c_str(), file, line );
    logger.forcedLog( log4cplus::ERROR_LOG_LEVEL, e.stackTrace(), file, line );
    throw;
}

} // end namespace util
