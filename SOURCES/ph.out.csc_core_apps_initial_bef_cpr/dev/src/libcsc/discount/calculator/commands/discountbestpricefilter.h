#ifndef GUARD_LIBCSC_DE_DISCOUNT_BEST_PRICE_FILTER_H
#define GUARD_LIBCSC_DE_DISCOUNT_BEST_PRICE_FILTER_H

#include <discount/calculator/commands/conditionalfilter.h>

namespace libcsc {
	namespace discount {

		class DiscountBestPriceFilter : public ConditionalFilter
		{
		protected:
			virtual void doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter);
			basar::Decimal getPrice(DiscountBaseValuePtr discount, IOrderBaseValueGetterPtr orderBaseValueGetter) const;
		};

	} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DE_DISCOUNT_BEST_PRICE_FILTER_H
