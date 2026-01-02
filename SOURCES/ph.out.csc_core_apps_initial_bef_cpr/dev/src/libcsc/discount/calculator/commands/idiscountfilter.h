#ifndef GUARD_LIBCSC_DE_DISCOUNT_IDISCOUNT_FILTER_H
#define GUARD_LIBCSC_DE_DISCOUNT_IDISCOUNT_FILTER_H

#include <discount/basevalues/discountbasevalue/idiscountbasevaluegetterptr.h>
#include <discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetter.h>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace libcsc {
	namespace discount {

		class IDiscountFilter
		{
			public:
				virtual void execute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter) = 0;
			protected:
				virtual void doExecute(DiscountBaseValueList& discountWorkingList, IOrderBaseValueGetterPtr orderBaseValueGetter) = 0;
		};

		typedef boost::shared_ptr< libcsc::discount::IDiscountFilter > IDiscountFilterPtr;

		typedef std::vector< IDiscountFilterPtr > DiscountFilterList;

	} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DE_DISCOUNT_IDISCOUNT_FILTER_H
