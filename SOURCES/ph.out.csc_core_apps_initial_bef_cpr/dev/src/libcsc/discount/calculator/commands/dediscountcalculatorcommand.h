#ifndef GUARD_LIBCSC_DE_DISCOUNT_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_DE_DISCOUNT_CALCULATOR_COMMAND_H

#include <discount/calculator/commands/idiscountfilter.h>
#include <discount/calculator/commands/discountcalculatorcommandbase.h>

#include <discount/resultprocessor/iresultprocessorptr.h>

#include <discount/basevalues/discountbasevalue/idiscountbasevaluegetterptr.h>
#include <discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h>
#include <discount/basevalues/discountbasevalue/discountbasevalueptr.h>
#include <discount/basevalues/discountbasevalue/discountbasevalue.h>

#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>

namespace libcsc {
namespace discount {

	class DEDiscountCalculatorCommand : public DiscountCalculatorCommandBase
	{
	public:
		DEDiscountCalculatorCommand();

		virtual ~DEDiscountCalculatorCommand();


		virtual const DiscountCalculatorResult& calculate() const;

		virtual void processResult() const;

		virtual void logHierarchy() const {}

		void injectFilters(DiscountFilterList filters);

	protected:
		void createDiscountWorkingList(DiscountBaseValueList& discountWorkingList) const;

	private:
		DiscountFilterList m_filters;
	};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DE_DISCOUNT_CALCULATOR_COMMAND_H
