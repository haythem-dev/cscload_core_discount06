#include "discount/calculator/commands/discountpriorityfilter.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"
#include "discount/basevalues/discountbasevalue/discountbasevalueptr.h"
#include <discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h>
#include <discount/calculator/commands/discountcalculatorcommandbase.h>
#include <logger/loggerpool.h>


namespace libcsc {
	namespace discount {

		void DiscountPriorityFilter::doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr /*orderBaseValueGetter*/)
		{
			BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountPriorityFilter::execute()");
			
			//1. find highest prio
			int highestPrio = 3;

			DiscountBaseValueList::iterator it = discountWorkingList.begin();
			while (it != discountWorkingList.end())
			{
				if (getPriority(*it) < highestPrio)
				{
					highestPrio = getPriority(*it);
				}
				++it;
			}


			//2. filter out all with lower prio
			it = discountWorkingList.begin();
			while (it != discountWorkingList.end())
			{
				if (getPriority(*it) > highestPrio)
				{
					it = discountWorkingList.erase(it);
					continue;
				}
				++it;
			}
		}

		int DiscountPriorityFilter::getPriority( DiscountBaseValuePtr discount ) const
		{
			BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountPriorityFilter::getPriority()");

			if ( DISC_TYPE_OPEN_CONCEPT_HZ == discount->getDiscountType() ||
				 DISC_TYPE_CLOSED_CONCEPT_HZ == discount->getDiscountType() ) // Concept: Herstellerzuteilung DA/MVDA
			{
				return 1;
			}

			if ( DISC_SPEC_HIGH_PRIORITY_OFFER == discount->getDiscountSpec() )			// Offer: high priority
			{
				return 1;
			}

			if ( DISC_TYPE_OPEN_CONCEPT == discount->getDiscountType() ||
				 DISC_TYPE_CLOSED_CONCEPT == discount->getDiscountType() ) // Concept: DA/MVDA
			{
				return 2;
			}

			return 3;																	// Offer: low priority (and all other)
		}
	} // end namespace discount
} // end namespace libcsc
