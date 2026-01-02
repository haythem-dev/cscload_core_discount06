#ifndef GUARD_LIBCSC_IBT_I_IBTBRANCH_REPOSITORY_PTR_H
#define GUARD_LIBCSC_IBT_I_IBTBRANCH_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace ibt {

	class IIbtBranchRepository;
	typedef boost::shared_ptr<libcsc::ibt::IIbtBranchRepository> IIbtBranchRepositoryPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTBRANCH_REPOSITORY_PTR_H
