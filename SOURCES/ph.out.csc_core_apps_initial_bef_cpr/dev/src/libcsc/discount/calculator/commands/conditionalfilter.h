#ifndef GUARD_LIBCSC_DE_DISCOUNT_CONDITIONAL_FILTER_H
#define GUARD_LIBCSC_DE_DISCOUNT_CONDITIONAL_FILTER_H

#include "idiscountfilter.h"

namespace libcsc {
	namespace discount {

		class ConditionalFilter : public IDiscountFilter
		{
		public:
			virtual void execute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter);
		};

	} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DE_DISCOUNT_CONDITIONAL_FILTER_H
