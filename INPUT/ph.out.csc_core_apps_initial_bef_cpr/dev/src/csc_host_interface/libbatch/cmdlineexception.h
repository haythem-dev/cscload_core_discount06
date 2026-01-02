//--------------------------------------------------------------------------------------------------//
/*! \file commandlineexception.h
 *  \brief exception from parsing the command line
 *  \author Dirk Kapusta
 *  \date 21.10.2008
 *  \version 00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBBATCH_COMMAND_LINE_EXCEPTION_H
#define GUARD_LIBBATCH_COMMAND_LINE_EXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libBatch  
{
namespace cmdLine
{

class CmdLineException : public basar::Exception
{
public:
	/*! \brief std constructor */
	CmdLineException( const basar::ExceptInfo& sInfo );
	/*! \brief std-destructor */
	~CmdLineException();

private:
	//!< forbidden
	CmdLineException();					
};

} // end namespace cmdLine
} // end namespace libBatch

#endif // GUARD_LIBBATCH_COMMAND_LINE_EXCEPTION_H
