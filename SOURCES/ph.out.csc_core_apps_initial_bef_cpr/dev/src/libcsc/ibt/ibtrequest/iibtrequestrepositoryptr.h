#ifndef GUARD_LIBCSC_IBT_I_IBTREQUEST_REPOSITORY_PTR_H
#define GUARD_LIBCSC_IBT_I_IBTREQUEST_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
	class IIbtRequestRepository;
	typedef boost::shared_ptr<libcsc::ibt::IIbtRequestRepository> IIbtRequestRepositoryPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUEST_REPOSITORY_PTR_H
