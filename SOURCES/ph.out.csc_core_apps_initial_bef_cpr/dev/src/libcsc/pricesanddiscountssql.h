#ifndef GUARD_LIBCSC_CUSTOMER_PRICESANDDISCOUNTSSQL_H
#define GUARD_LIBCSC_CUSTOMER_PRICESANDDISCOUNTSSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
	namespace customer {

		class  PricesandDiscountsSql
		{
		public:
			~PricesandDiscountsSql();

			static const basar::VarString GetPricesandDiscountsStatusFlagsQuery(const basar::Int16 branchNo,
				const basar::Int32 customerNo, const basar::Int32 orderNo, const basar::Int32 orderDate);

		private:
			PricesandDiscountsSql();
			PricesandDiscountsSql& operator=(const  PricesandDiscountsSql&);
		};

	} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_PRICESANDDISCOUNTSSQL_H