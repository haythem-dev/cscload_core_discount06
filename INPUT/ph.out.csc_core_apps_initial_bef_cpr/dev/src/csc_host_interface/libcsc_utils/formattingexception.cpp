//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief 
 *  \author 
 *  \date 
 *  \version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include "formattingexception.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace recordtypes
{

	FormattingException::FormattingException( const basar::ExceptInfo& sInfo )
	: BasarException( sInfo, "FormattingException" )
	{
	}

	FormattingException::~FormattingException()
	{
	}

}
}
} // end namespace util
