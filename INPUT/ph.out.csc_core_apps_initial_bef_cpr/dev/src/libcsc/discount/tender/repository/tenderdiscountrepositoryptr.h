#ifndef GUARD_LIBCSC_TENDER_DISCOUNT_REPOSITORY_PTR_H
#define GUARD_LIBCSC_TENDER_DISCOUNT_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class TenderDiscountRepository;
typedef boost::shared_ptr<libcsc::discount::TenderDiscountRepository> TenderDiscountRepositoryPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_DISCOUNT_REPOSITORY_PTR_H
