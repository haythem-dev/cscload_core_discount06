//---------------------------------------------------------------------------//
/*! \file
 *  \brief		exception from mail sending
 *  \author		Steffen Heinlein
 *  \date		25.06.2012
 *  \version	00.00.00.01 first version
 */ //-----------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_MAILEXCEPTION_H
#define GUARD_LIBCSC_UTILS_MAILEXCEPTION_H

#include <libbasarcmnutil_exceptions.h>

namespace libcsc_utils
{

	class MailException : public basar::Exception
	{
		public:
			/*! \brief std constructor */
			MailException( const basar::ExceptInfo& sInfo );

			/*! \brief std-destructor */
			~MailException();

		private:
			//!< forbidden
			MailException();		
	};

} // end namespace domMod  

#endif // GUARD_LIBCSC_UTILS_MAILEXCEPTION_H

