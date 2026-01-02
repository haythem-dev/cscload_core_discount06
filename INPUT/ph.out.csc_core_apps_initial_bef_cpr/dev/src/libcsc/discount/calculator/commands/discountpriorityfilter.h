#ifndef GUARD_LIBCSC_DE_DISCOUNT_PRIORITY_FILTER_H
#define GUARD_LIBCSC_DE_DISCOUNT_PRIORITY_FILTER_H

#include <discount/calculator/commands/conditionalfilter.h>

namespace libcsc {
	namespace discount {

		class DiscountPriorityFilter : public ConditionalFilter
		{
		protected:
			virtual void doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter);
			int getPriority(DiscountBaseValuePtr discount) const;
		};

	} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DE_DISCOUNT_PRIORITY_FILTER_H
