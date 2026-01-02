#ifndef GUARD_LIBCSC_IBT_I_IBTREQUEST__PTR_H
#define GUARD_LIBCSC_IBT_I_IBTREQUEST__PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc 
{
namespace ibt 
{
	class IIbtRequest;
	typedef boost::shared_ptr<libcsc::ibt::IIbtRequest> IIbtRequestPtr;

	typedef std::list<libcsc::ibt::IIbtRequestPtr> IIbtRequestCollection;
	typedef boost::shared_ptr<libcsc::ibt::IIbtRequestCollection> IIbtRequestCollectionPtr;

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUEST__PTR_H
