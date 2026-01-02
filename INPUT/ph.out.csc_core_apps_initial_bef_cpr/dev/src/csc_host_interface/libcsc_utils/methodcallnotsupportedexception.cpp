//-----------------------------------------------------------------------------------------------------------//
/*! \brief  Throw exception if method is not alloed to be called in the invoked context.
 *  \author Steffen Heinlein
 *  \date	02.07.2012
 */
//-----------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------//
// include section
//-----------------------------------------------------------------------------------------------------------//
#include "methodcallnotsupportedexception.h"

//-----------------------------------------------------------------------------------------------------------//
// class definition section
//-----------------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
    MethodCallNotSupportedException::MethodCallNotSupportedException( const basar::ExceptInfo & sInfo )    
	: BasarException( sInfo, "MethodCallNotSupportedException" )
    {
    }

    MethodCallNotSupportedException::~MethodCallNotSupportedException()
    {
    }

} // namespace core

