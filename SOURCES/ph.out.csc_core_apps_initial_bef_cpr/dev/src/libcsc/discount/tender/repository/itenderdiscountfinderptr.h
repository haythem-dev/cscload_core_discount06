#ifndef GUARD_LIBCSC_I_TENDER_DISCOUNT_FINDER_PTR_H
#define GUARD_LIBCSC_I_TENDER_DISCOUNT_FINDER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class ITenderDiscountFinder;
typedef boost::shared_ptr<libcsc::discount::ITenderDiscountFinder> ITenderDiscountFinderPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_TENDER_DISCOUNT_FINDER_PTR_H
