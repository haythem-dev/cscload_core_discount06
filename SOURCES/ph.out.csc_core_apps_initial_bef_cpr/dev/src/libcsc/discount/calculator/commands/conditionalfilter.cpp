#include "discount/calculator/commands/conditionalfilter.h"


namespace libcsc {
	namespace discount {
		void ConditionalFilter::execute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter)
		{
			if (discountWorkingList.size() == 0 || discountWorkingList.size() == 1)
			{
				return;
			}
			doExecute(discountWorkingList, orderBaseValueGetter);
		}
	} // end namespace discount
} // end namespace libcsc
