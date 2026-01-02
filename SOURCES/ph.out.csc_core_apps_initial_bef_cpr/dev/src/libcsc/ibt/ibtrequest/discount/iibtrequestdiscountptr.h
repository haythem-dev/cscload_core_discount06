#ifndef GUARD_LIBCSC_IBT_I_IBTREQUESTDISCOUNT_PTR_H
#define GUARD_LIBCSC_IBT_I_IBTREQUESTDISCOUNT_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc
{
namespace ibt
{
	class IIbtRequestDiscount;
	typedef boost::shared_ptr<libcsc::ibt::IIbtRequestDiscount> IIbtRequestDiscountPtr;

	typedef std::list<libcsc::ibt::IIbtRequestDiscountPtr> IIbtRequestDiscountCollection;


} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUESTDISCOUNT_PTR_H
