#ifndef GUARD_LIBCSC_DE_DISCOUNT_VISIBILITY_FILTER_H
#define GUARD_LIBCSC_DE_DISCOUNT_VISIBILITY_FILTER_H

#include <discount/calculator/commands/unconditionalfilter.h>

namespace libcsc {
	namespace discount {

		class DiscountVisibilityFilter : public UnconditionalFilter
		{
		protected:
			virtual void doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter);
		};

	} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DE_DISCOUNT_VISIBILITY_FILTER_H
