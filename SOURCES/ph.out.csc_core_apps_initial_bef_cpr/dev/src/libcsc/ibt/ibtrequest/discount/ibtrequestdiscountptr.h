#ifndef GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_PTR_H
#define GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc
{
namespace ibt
{
	class IbtRequestDiscount;
	typedef boost::shared_ptr<libcsc::ibt::IbtRequestDiscount> IbtRequestDiscountPtr;

	typedef std::list<libcsc::ibt::IbtRequestDiscountPtr> IbtRequestDiscountCollection;

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_PTR_H
