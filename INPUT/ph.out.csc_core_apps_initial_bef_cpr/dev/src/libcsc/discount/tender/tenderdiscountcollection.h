#ifndef GUARD_LIBCSC_TENDER_DISCOUNT_COLLECTION_H
#define GUARD_LIBCSC_TENDER_DISCOUNT_COLLECTION_H

#include <discount/tender/tenderdiscountptr.h>
#include <vector>

namespace libcsc
{
namespace discount
{
typedef std::vector<libcsc::discount::TenderDiscountPtr> TenderDiscountList;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_DISCOUNT_COLLECTION_H
