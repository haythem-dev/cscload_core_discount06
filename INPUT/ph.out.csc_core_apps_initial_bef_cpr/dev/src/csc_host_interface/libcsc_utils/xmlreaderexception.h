//--------------------------------------------------------------------------------------------------//
/*! \file		xmlreaderexception.h
 *  \brief      exception for XmlStreamReader
 *  \author
 *  \date
 */
//--------------------------------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_XML_READER_EXCEPTION_H
#define GUARD_LIBCSC_UTILS_XML_READER_EXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	class XmlReaderException : public basar::Exception
	{
	public:
		/*! \brief std constructor */
		XmlReaderException(const basar::ExceptInfo& sInfo);
		/*! \brief std-destructor */
		~XmlReaderException();

	private:
		//!< forbidden
		XmlReaderException();
		//XmlReaderException( XmlReaderException& );
		XmlReaderException& operator=(XmlReaderException&);
	};
} // end namespace csc_phatra

#endif // end GUARD_LIBCSC_UTILS_XML_READER_EXCEPTION_H
