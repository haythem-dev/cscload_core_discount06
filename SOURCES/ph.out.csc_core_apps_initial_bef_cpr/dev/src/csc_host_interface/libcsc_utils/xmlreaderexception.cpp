//--------------------------------------------------------------------------------------------------//
/*! \file xmlreaderexception.cpp
 *  \brief      exception for xmlStreamReader
 *  \author
 *  \date
 */
//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
//#include "cmnexcept.h"
#include <libbasar_definitions.h>
#include "xmlreaderexception.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
XmlReaderException::XmlReaderException(const basar::ExceptInfo& sInfo) :
		BasarException(sInfo, "XmlReaderException")
{
}

XmlReaderException::~XmlReaderException()
{
}
} // end namespace csc_phatra
