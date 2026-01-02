//--------------------------------------------------------------------------------------------------//
/*! \file commandlineexception.cpp
 *  \brief exception from parsing the command line
 *  \author Dirk Kapusta
 *  \date 21.10.2008
 *  \version 00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
// following include directive must be the first include !
// this cpp file must be compiled for all(!) configurations with settings:
//	   /Yu"cmnexcept.h" /Fp$(IntDir)/cmnexcept.pch
//#include "cmnexcept.h"
#include <libbasar_definitions.h>
#include "cmdlineexception.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libBatch  
{
namespace cmdLine
{

CmdLineException::CmdLineException( const basar::ExceptInfo& sInfo )
: BasarException( sInfo, "CmdLineException" )
{
}

CmdLineException::~CmdLineException()
{
}

} // end namespace cmdLine
} // end namespace libBatch
