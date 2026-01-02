#ifndef GUARD_LIBCSC_IBT_IBTBRANCH_REPOSITORY_PTR_H
#define GUARD_LIBCSC_IBT_IBTBRANCH_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
	class IbtBranchRepository;
	typedef boost::shared_ptr<libcsc::ibt::IbtBranchRepository> IbtBranchRepositoryPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTBRANCH_REPOSITORY_PTR_H
