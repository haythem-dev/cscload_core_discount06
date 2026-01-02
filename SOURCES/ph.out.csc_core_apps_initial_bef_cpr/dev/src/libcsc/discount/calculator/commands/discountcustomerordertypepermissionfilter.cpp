#include "discount/calculator/commands/discountcustomerordertypepermissionfilter.h"
#include "discount/calculator/commands/discountcalculatorchaincommandbase.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"

#include <logger/loggerpool.h>

namespace libcsc {
	namespace discount {

		void DiscountCustomerOrderTypePermissionFilter::doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter)
		{
			BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountCustomerOrderTypePermissionFilter::execute()");

			if (true == orderBaseValueGetter->isCalcNetPrice())
				return;

			DiscountBaseValueList::iterator it = discountWorkingList.begin();
			while (it != discountWorkingList.end())
			{
				if ((*it)->getDiscountSpec() == DISC_SPEC_DEFAULT && (*it)->getDiscountType() == DISC_TYPE_DEFAULT)
				{
					it = discountWorkingList.erase(it);
					continue;
				}
				++it;
			}
		}

	} // end namespace discount
} // end namespace libcsc
