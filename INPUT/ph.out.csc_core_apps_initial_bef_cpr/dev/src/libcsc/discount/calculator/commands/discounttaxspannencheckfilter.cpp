#include "discount/calculator/commands/discounttaxspannencheckfilter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"
#include <logger/loggerpool.h>

namespace libcsc {
	namespace discount {

		DiscountTaxSpannenCheckFilter::DiscountTaxSpannenCheckFilter(const basar::Decimal& taxSpannenFestBetrag) : UnconditionalFilter()
		{
			m_TaxSpannenFestBetrag = taxSpannenFestBetrag;
		}

		void DiscountTaxSpannenCheckFilter::doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter)
		{
			BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountTaxSpannenCheckFilter::execute()");

			if (false == orderBaseValueGetter->isTaxSpannenCheckNecessary())
				return;

			DiscountBaseValueList::iterator it = discountWorkingList.begin();
			while (it != discountWorkingList.end())
			{
				// first check lower limit (discount price < GEP+70ct?)
				if ((*it)->getFixedPrice() < orderBaseValueGetter->getExFactoryPrice() + m_TaxSpannenFestBetrag)
				{
					(*it)->setFixedPrice(orderBaseValueGetter->getExFactoryPrice() + m_TaxSpannenFestBetrag);
				}

				// then check upper limit (discount price > AEP?)
				if ((*it)->getFixedPrice() > orderBaseValueGetter->getItemPrice())
				{
					it = discountWorkingList.erase(it);
					continue;
				}
				++it;
			}
		}

	} // end namespace discount
} // end namespace libcsc
