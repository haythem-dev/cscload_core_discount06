//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include "setupsignalhandlingexception.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{

	//--------------------------------------------------------------------------------------------------//
	SetupSignalHandlingException::SetupSignalHandlingException( const basar::ExceptInfo& sInfo )
		: BasarException( sInfo, "SetupSignalHandlingException" )
	{}

	//--------------------------------------------------------------------------------------------------//
	SetupSignalHandlingException::~SetupSignalHandlingException()
	{}

} // namespace util
