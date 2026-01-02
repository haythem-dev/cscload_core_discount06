#ifndef GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVEREPOSITORYPTR_H
#define GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVEREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc 
{
	namespace document 
	{
		class NarcoticArchiveRepository;
		typedef boost::shared_ptr<NarcoticArchiveRepository> NarcoticArchiveRepositoryPtr;

	} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVEREPOSITORYPTR_H
