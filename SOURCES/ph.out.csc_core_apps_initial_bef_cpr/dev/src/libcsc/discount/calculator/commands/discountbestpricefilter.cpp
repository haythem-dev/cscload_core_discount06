#include <discount/calculator/commands/discountbestpricefilter.h>
#include <discount/calculator/commands/discountcalculatorcommandbase.h>
#include <discount/basevalues/discountbasevalue/discountbasevalue.h>

#include <logger/loggerpool.h>


namespace libcsc {
	namespace discount {

		void DiscountBestPriceFilter::doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter)
		{
			BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountBestPriceFilter::execute()");
			
			// 1. find best price
			DiscountBaseValueList::iterator it = discountWorkingList.begin();
			DiscountBaseValueList::iterator posFound = discountWorkingList.begin();

			basar::Decimal bestPrice(getPrice(*it, orderBaseValueGetter));

			if (it != discountWorkingList.end())
			{
				++it;
			}

			basar::Decimal priceZero(0.0);

			while (it != discountWorkingList.end())
			{
				basar::Decimal currentPrice = getPrice(*it, orderBaseValueGetter);

				if (currentPrice <= bestPrice && currentPrice > priceZero)
				{
					bestPrice = currentPrice;
					posFound = it;
				}

				++it;
			}


			it = discountWorkingList.begin();

			while (it != discountWorkingList.end())
			{
				if (it != posFound)
				{
					it = discountWorkingList.erase(it);

					continue;
				}

				++it;
			}
		}

		basar::Decimal DiscountBestPriceFilter::getPrice(DiscountBaseValuePtr discount, IOrderBaseValueGetterPtr orderBaseValueGetter) const
		{
			BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountBestPriceFilter::getPrice()");

			basar::Decimal price(0.0);

			if ( DISC_TYPE_SURCHARGE_EXF == discount->getDiscountType() ) // Personal GEP+7%
			{
				price = orderBaseValueGetter->getExFactoryPrice() * ( 1 + ( discount->getSurchargePct() / 100 ) );

				return price;
			}

			price = discount->getFixedPrice();

			return price;
		}

	} // end namespace discount
} // end namespace libcsc
