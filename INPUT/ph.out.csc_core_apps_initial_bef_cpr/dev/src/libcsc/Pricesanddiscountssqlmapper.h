#ifndef GUARD_LIBCSC_CUSTOMER_PRICESANDDISCOUNTSSQLMAPPER_H
#define GUARD_LIBCSC_CUSTOMER_PRICESANDDISCOUNTSSQLMAPPER_H

#include <customer/PricesandDiscounts/OR-Mapper/pricesanddiscountsmapperbase.h>

#include <libbasardbsql_resultsetref.h>
#include <libbasar_definitions.h>

namespace libcsc {
	namespace customer {

		class PricesandDiscountsSqlMapper : public PricesandDiscountsMapperBase
		{
		public:
			PricesandDiscountsSqlMapper(
				PricesandDiscountsPtr cuco,
				const basar::db::sql::ResultsetRef resultSet
			);
			virtual ~PricesandDiscountsSqlMapper();

			static const basar::VarString getSelectSQL(const basar::Int16 branchNo,
				const basar::Int32 customerNoFrom, const basar::Int32 articleNoFrom,
				const basar::Int32 maxPriceElements, const basar::Int32 customerNoFilter);

		protected:
			virtual void doMap();

		private:
			PricesandDiscountsSqlMapper(const  PricesandDiscountsSqlMapper&);
			PricesandDiscountsSqlMapper& operator=(const  PricesandDiscountsSqlMapper&);

			const basar::db::sql::ResultsetRef  m_ResultSet;
		};

	} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_PRICESANDDISCOUNTSSQLMAPPER_H

