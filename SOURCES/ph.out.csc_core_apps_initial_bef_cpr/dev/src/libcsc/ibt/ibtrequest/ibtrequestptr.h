#ifndef GUARD_LIBCSC_IBT_IBTREQUEST_PTR_H
#define GUARD_LIBCSC_IBT_IBTREQUEST_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc
{
namespace ibt
{
	class IbtRequest;
	typedef boost::shared_ptr<libcsc::ibt::IbtRequest> IbtRequestPtr;

	typedef std::list<libcsc::ibt::IbtRequestPtr> IbtRequestCollection;

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUEST_PTR_H
