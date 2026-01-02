#ifndef GUARD_LIBCSC_I_TENDER_DISCOUNT_FINDER_H
#define GUARD_LIBCSC_I_TENDER_DISCOUNT_FINDER_H

#include <discount/tender/repository/tenderdiscountsearchparams.h>
#include <discount/tender/tenderdiscountcollectionptr.h>

namespace libcsc
{
namespace discount
{
class ITenderDiscountFinder
{
public:
	virtual ~ITenderDiscountFinder() {}

	virtual void reset() = 0;
	virtual TenderDiscountListPtr findByPattern( const TenderDiscountSearchParams & params ) const = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_TENDER_DISCOUNT_FINDER_H
