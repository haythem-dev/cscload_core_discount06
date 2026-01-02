//--------------------------------------------------------------------------------------------------//
/*! \file		PXVBComponentBadStateException.h
 *  \brief      exception for failed initialization of pxVerbund objects
 *  \author
 *  \date
 */
//--------------------------------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_PXVBCOMPONENTBADSTATEEXCEPTION_H
#define GUARD_LIBCSC_UTILS_PXVBCOMPONENTBADSTATEEXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	class PXVBComponentBadStateException : public basar::Exception
	{
	public:
		/*! \brief std constructor */
		PXVBComponentBadStateException(const basar::ExceptInfo& sInfo);
		/*! \brief std-destructor */
		~PXVBComponentBadStateException();

	private:
		//!< forbidden
		PXVBComponentBadStateException();
		PXVBComponentBadStateException& operator=(PXVBComponentBadStateException&);
	};
} // end namespace util

#endif // GUARD_LIBCSC_UTILS_PXVBCOMPONENTBADSTATEEXCEPTION_H
