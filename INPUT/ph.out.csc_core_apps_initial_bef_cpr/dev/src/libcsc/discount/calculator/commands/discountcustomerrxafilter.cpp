#include "discount/calculator/commands/discountcustomerrxafilter.h"
#include <discount/calculator/commands/discountcalculatorcommandbase.h>
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"
#include <logger/loggerpool.h>

// Special prices that will be invalidated by invoicing:
// KUI - RXA :
// - all articles : KUI-RXA = ‚S‘
// - OTC / FW : KUI-RXA = ‚O’
// - prescription :
//   - KUI-RXA = ‚J‘
//   - KUI-RXA = ‚H‘, AEP > 1238,50
//   - KUI-RXA = ‚X‘, AEP > 5000,00

namespace libcsc {
	namespace discount {

		void DiscountCustomerRXAFilter::doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter)
		{
			BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountCustomerRXAFilter::execute()");

			DiscountBaseValueList::iterator it = discountWorkingList.begin();
			while (it != discountWorkingList.end())
			{
				if ((*it)->getDiscountSpec() != DISC_SPEC_DEFAULT || (*it)->getDiscountType() != DISC_TYPE_DEFAULT)
				{
					++it;
					continue;
				}

				if ('S' == orderBaseValueGetter->getCustomerRXAFlag()) // alle raus
				{
					BLOG_TRACE(LoggerPool::getLoggerDiscountCalc(), "Erase RXA=S");
					it = discountWorkingList.erase(it);
					continue;
				}
				if ('O' == orderBaseValueGetter->getCustomerRXAFlag()) // wenn nicht rezeptpflichtig, dann raus
				{
					if (false == orderBaseValueGetter->isRezeptPflichtig())
					{
						BLOG_TRACE(LoggerPool::getLoggerDiscountCalc(), "Erase RXA=O");
						it = discountWorkingList.erase(it);
						continue;
					}
				}
				if ('J' == orderBaseValueGetter->getCustomerRXAFlag()) // wenn rezeptpflichtig, dann raus
				{
					if (true == orderBaseValueGetter->isRezeptPflichtig())
					{
						BLOG_TRACE(LoggerPool::getLoggerDiscountCalc(), "Erase RXA=J");
						it = discountWorkingList.erase(it);
						continue;
					}
				}
				if ('H' == orderBaseValueGetter->getCustomerRXAFlag()) // wenn rezeptpflichtig, und AEP > 1238,50 dann raus
				{
					if (true == orderBaseValueGetter->isRezeptPflichtig() && basar::Decimal(1238.50) < orderBaseValueGetter->getItemPrice())
					{
						BLOG_TRACE(LoggerPool::getLoggerDiscountCalc(), "Erase RXA=H");
						it = discountWorkingList.erase(it);
						continue;
					}
				}
				if ('X' == orderBaseValueGetter->getCustomerRXAFlag()) // wenn rezeptpflichtig, und AEP > 5000,00 dann raus
				{
					if (true == orderBaseValueGetter->isRezeptPflichtig() && basar::Decimal(5000.00) < orderBaseValueGetter->getItemPrice())
					{
						BLOG_TRACE(LoggerPool::getLoggerDiscountCalc(), "Erase RXA=X");
						it = discountWorkingList.erase(it);
						continue;
					}
				}
				++it;
			}
		}

	} // end namespace discount
} // end namespace libcsc
