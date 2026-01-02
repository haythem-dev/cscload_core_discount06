#ifndef GUARD_LIBCSC_TENDER_DISCOUNT_COLLECTION_PTR_H
#define GUARD_LIBCSC_TENDER_DISCOUNT_COLLECTION_PTR_H

#include <discount/tender/tenderdiscountcollection.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
typedef boost::shared_ptr<libcsc::discount::TenderDiscountList> TenderDiscountListPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_DISCOUNT_COLLECTION_PTR_H
