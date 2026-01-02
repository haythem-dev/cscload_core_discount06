//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      exception indicating soft kill signals
 *  \author     Heinlein Steffen
 *  \date       15.06.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_SOFTKILLEXCEPTION_H
#define GUARD_LIBCSC_UTILS_SOFTKILLEXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{

	class SoftKillException : public basar::Exception
	{
		public:
			SoftKillException( const basar::ExceptInfo& sInfo );
			~SoftKillException();

		private:
			SoftKillException();							
			SoftKillException& operator=( SoftKillException& );
	};

}

#endif 

