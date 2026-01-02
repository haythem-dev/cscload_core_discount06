#ifndef GUARD_LIBCSC_DE_DISCOUNT_TAX_SPANNEN_CHECK_FILTER_H
#define GUARD_LIBCSC_DE_DISCOUNT_TAX_SPANNEN_CHECK_FILTER_H

#include <discount/calculator/commands/unconditionalfilter.h>

namespace libcsc {
	namespace discount {

		class DiscountTaxSpannenCheckFilter : public UnconditionalFilter
		{
		public:
			DiscountTaxSpannenCheckFilter(const basar::Decimal& TaxSpannenFestBetrag);
		protected:
			virtual void doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter);
		private:
			basar::Decimal m_TaxSpannenFestBetrag;
		};

	} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DE_DISCOUNT_TAX_SPANNEN_CHECK_FILTER_H
