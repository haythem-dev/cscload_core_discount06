#include <discount/calculator/commands/discountvisibilityfilter.h>
#include <discount/calculator/commands/discountcalculatorcommandbase.h>
#include <discount/basevalues/discountbasevalue/discountbasevalue.h>
#include <logger/loggerpool.h>

namespace libcsc {
	namespace discount {

		void DiscountVisibilityFilter::doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter)
		{
			BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountVisibilityFilter::doExecute()");

			DiscountBaseValueList::iterator it = discountWorkingList.begin();
			while ( it != discountWorkingList.end() )
			{
				if ( DISC_TYPE_CLOSED_CONCEPT == (*it)->getDiscountType())
				{
					if (orderBaseValueGetter->isRezeptPflichtig() || orderBaseValueGetter->isApothekenPflichtig())
						(*it)->setFixedPrice(basar::Decimal(0.0));
				}
				++it;
			}
		}

	} // end namespace discount
} // end namespace libcsc
