//---------------------------------------------------------------------------//
/*! \file		
 *  \brief		exception from mail sending
 *  \author		Steffen Heinlein
 *  \date		25.06.2012
 *  \version	00.00.00.01 first version
 */ //-----------------------------------------------------------------------//

#include "mailexception.h"

namespace libcsc_utils  
{
	MailException::MailException( const basar::ExceptInfo& sInfo )
	: BasarException( sInfo, "MailException" )
	{
	}

	MailException::~MailException()
	{
	}

} // end namespace domMod
