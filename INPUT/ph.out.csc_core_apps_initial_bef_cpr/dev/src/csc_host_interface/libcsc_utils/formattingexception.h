//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      exception indicating error with formatting
 *  \author     Steffen Heinlein
 *  \date       21.03.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_FORMATTINGEXCEPTION_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_FORMATTINGEXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace recordtypes
{	

	class FormattingException : public basar::Exception
	{
		public:			
			FormattingException( const basar::ExceptInfo& sInfo );			
			~FormattingException();

		private:			
			FormattingException();								
			FormattingException& operator=( FormattingException& );
	};
} 
}
}

#endif 

