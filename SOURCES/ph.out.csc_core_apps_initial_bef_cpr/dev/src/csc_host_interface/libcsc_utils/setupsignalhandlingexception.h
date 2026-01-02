#ifndef GUARD_LIBCSC_UTILS_SETUPSIGNALHANDLINGEXCEPTION_H
#define GUARD_LIBCSC_UTILS_SETUPSIGNALHANDLINGEXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{	

	class SetupSignalHandlingException : public basar::Exception
	{
		public:			
			SetupSignalHandlingException( const basar::ExceptInfo& sInfo );
			~SetupSignalHandlingException();

		private:			
			SetupSignalHandlingException();					    			
			SetupSignalHandlingException& operator=( SetupSignalHandlingException& );
	};

} // namespace util

#endif // end GUARD_LIBCSC_UTILS_SETUPSIGNALHANDLINGEXCEPTION_H

