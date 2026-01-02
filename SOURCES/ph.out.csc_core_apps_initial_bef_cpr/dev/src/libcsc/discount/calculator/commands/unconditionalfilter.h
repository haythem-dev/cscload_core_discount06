#ifndef GUARD_LIBCSC_DE_DISCOUNT_UNCONDITIONAL_FILTER_H
#define GUARD_LIBCSC_DE_DISCOUNT_UNCONDITIONAL_FILTER_H

#include "idiscountfilter.h"

namespace libcsc {
	namespace discount {

		class UnconditionalFilter : public IDiscountFilter
		{
		public:
			virtual void execute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter);
		};

	} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DE_DISCOUNT_UNCONDITIONAL_FILTER_H