//-----------------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      Throw exception if method is not alloed to be called in the invoked context.
 *  \author     Steffen Heinlein
 *  \date	    02.07.2012
 *  \version    00.00.00.01 first version
 */
//-----------------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_METHODCALLNOTSUPPORTEDEXCEPTION_H
#define GUARD_LIBCSC_UTILS_METHODCALLNOTSUPPORTEDEXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//-----------------------------------------------------------------------------------------------------------//
// class declaration section
//-----------------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
    class MethodCallNotSupportedException : public basar::Exception
    {
        public:
	        MethodCallNotSupportedException( const basar::ExceptInfo & sInfo );
	        ~MethodCallNotSupportedException();

        private:
	        MethodCallNotSupportedException();					
    };

} // namespace util

#endif // GUARD_LIBCSC_UTILS_METHODCALLNOTSUPPORTEDEXCEPTION_H
