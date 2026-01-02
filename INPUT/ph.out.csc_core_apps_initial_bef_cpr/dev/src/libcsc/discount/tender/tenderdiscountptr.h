#ifndef GUARD_LIBCSC_TENDER_DISCOUNT_PTR_H
#define GUARD_LIBCSC_TENDER_DISCOUNT_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class TenderDiscount;
typedef boost::shared_ptr<libcsc::discount::TenderDiscount> TenderDiscountPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_DISCOUNT_PTR_H
