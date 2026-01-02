#ifndef GUARD_LIBCSC_IBT_IBTREQUESTREMARK_PTR_H
#define GUARD_LIBCSC_IBT_IBTREQUESTREMARK_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc
{
namespace ibt
{
	class IbtRequestRemark;
	typedef boost::shared_ptr<libcsc::ibt::IbtRequestRemark> IbtRequestRemarkPtr;

	typedef std::list<libcsc::ibt::IbtRequestRemarkPtr> IbtRequestRemarkCollection;

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUESTREMARK_PTR_H
