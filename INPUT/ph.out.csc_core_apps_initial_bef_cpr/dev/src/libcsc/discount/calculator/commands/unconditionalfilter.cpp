#include <discount/calculator/commands/unconditionalfilter.h>


namespace libcsc {
	namespace discount {

		void UnconditionalFilter::execute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter)
		{
			if (discountWorkingList.size() == 0)
			{
				return;
			}
			else
			{
				return doExecute(discountWorkingList, orderBaseValueGetter);
			}
		}
	} // end namespace discount
} // end namespace libcsc
