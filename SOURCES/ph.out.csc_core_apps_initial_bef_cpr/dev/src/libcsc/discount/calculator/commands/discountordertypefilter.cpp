#include <discount/calculator/commands/discountordertypefilter.h>
#include <discount/calculator/commands/discountcalculatorcommandbase.h>
#include <discount/basevalues/discountbasevalue/discountbasevalue.h>
#include <logger/loggerpool.h>

namespace libcsc {
	namespace discount {

		void DiscountOrderTypeFilter::doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter)
		{
			BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountOrderTypeFilter::execute()");
			
			DiscountBaseValueList::iterator it = discountWorkingList.begin();
			while (it != discountWorkingList.end())
			{
				if (orderBaseValueGetter->getOrderType() == "HZ")
				{
					if (DISC_TYPE_OPEN_CONCEPT_HZ != (*it)->getDiscountType() && DISC_TYPE_CLOSED_CONCEPT_HZ != (*it)->getDiscountType())
					{
						it = discountWorkingList.erase(it);
						continue;
					}
				}
				else
				{
					if (DISC_TYPE_OPEN_CONCEPT_HZ == (*it)->getDiscountType() || DISC_TYPE_CLOSED_CONCEPT_HZ == (*it)->getDiscountType())
					{
						it = discountWorkingList.erase(it);
						continue;
					}
				}
				++it;
			}
		}

	} // end namespace discount
} // end namespace libcsc
