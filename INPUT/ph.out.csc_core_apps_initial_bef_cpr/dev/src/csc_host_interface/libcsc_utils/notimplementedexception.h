//--------------------------------------------------------------------------------------------------//
/*! \file		notimplementedexception.h
 *  \brief      exception for missing implementations
 *  \author
 *  \date
 */
//--------------------------------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_NOTIMPLEMENTEDEXCEPTION_H
#define GUARD_LIBCSC_UTILS_NOTIMPLEMENTEDEXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	class NotImplementedException : public basar::Exception
	{
	public:
		/*! \brief std constructor */
		NotImplementedException(const basar::ExceptInfo& sInfo);
		/*! \brief std-destructor */
		~NotImplementedException();

	private:
		//!< forbidden
		NotImplementedException();
		NotImplementedException& operator=(NotImplementedException&);
	};
} // end namespace util

#endif // end GUARD_LIBCSC_UTILS_NOTIMPLEMENTEDEXCEPTION_H
