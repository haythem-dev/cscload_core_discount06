//--------------------------------------------------------------------------------------------------//
/*! \file		PutenvFailedException.h
 *  \brief      exception for failed putenv
 *  \author
 *  \date
 */
//--------------------------------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_PUTENVFAILEDEXCEPTION_H
#define GUARD_LIBCSC_UTILS_PUTENVFAILEDEXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	class PutenvFailedException : public basar::Exception
	{
	public:
		/*! \brief std constructor */
		PutenvFailedException(const basar::ExceptInfo& sInfo);
		/*! \brief std-destructor */
		~PutenvFailedException();

	private:
		//!< forbidden
		PutenvFailedException();
		PutenvFailedException& operator=(PutenvFailedException&);
	};
} // end namespace libcsc_utils

#endif // end GUARD_LIBCSC_UTILS_PUTENVFAILEDEXCEPTION_H
