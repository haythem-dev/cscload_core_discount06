#ifndef GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVEPTR_H
#define GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVEPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc 
{
	namespace document 
	{

		class NarcoticArchive;
		typedef boost::shared_ptr<NarcoticArchive> NarcoticArchivePtr;

	} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVEPTR_H
