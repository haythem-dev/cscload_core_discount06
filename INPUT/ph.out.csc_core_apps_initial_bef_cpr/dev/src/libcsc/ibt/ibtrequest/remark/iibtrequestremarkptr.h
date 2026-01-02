#ifndef GUARD_LIBCSC_IBT_I_IBTREQUESTREMARK_PTR_H
#define GUARD_LIBCSC_IBT_I_IBTREQUESTREMARK_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc
{
namespace ibt
{
	class IIbtRequestRemark;
	typedef boost::shared_ptr<libcsc::ibt::IIbtRequestRemark> IIbtRequestRemarkPtr;

	typedef std::list<libcsc::ibt::IIbtRequestRemarkPtr> IIbtRequestRemarkCollection;


} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUESTREMARK_PTR_H
