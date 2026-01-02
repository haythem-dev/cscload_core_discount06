//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      exception indicating missing remote procedure
 *  \author     Steffen Heinlein
 *  \date       22.06.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_MISSINGDEPENDENCYINJECTIONEXCEPTION_H
#define GUARD_LIBCSC_UTILS_MISSINGDEPENDENCYINJECTIONEXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{	

	class MissingDependencyInjectionException : public basar::Exception
	{
		public:			
			MissingDependencyInjectionException( const basar::ExceptInfo& sInfo );
			~MissingDependencyInjectionException();

		private:			
			MissingDependencyInjectionException();					    			
			MissingDependencyInjectionException& operator=( MissingDependencyInjectionException& );
	};

} // namespace util

#endif // end GUARD_LIBCSC_UTILS_MISSINGDEPENDENCYINJECTIONEXCEPTION_H

