//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      exception indicating invalid status changes
 *  \author     Heinlein Steffen
 *  \date       10.07.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_INVALIDSTATUSCHANGEEXCEPTION_H
#define GUARD_LIBCSC_UTILS_INVALIDSTATUSCHANGEEXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{

	class InvalidStatusChangeException : public basar::Exception
	{
		public:
			InvalidStatusChangeException( const basar::ExceptInfo& sInfo );
			~InvalidStatusChangeException();

		private:
			InvalidStatusChangeException();							
			InvalidStatusChangeException& operator=( InvalidStatusChangeException& );
	};

}

#endif 

