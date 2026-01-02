#ifndef GUARD_LIBCSC_IBT_IBTRESPONSE_REPOSITORY_PTR_H
#define GUARD_LIBCSC_IBT_IBTRESPONSE_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
	class IbtResponseRepository;
	typedef boost::shared_ptr<libcsc::ibt::IbtResponseRepository> IbtResponseRepositoryPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTRESPONSE_REPOSITORY_PTR_H
