#ifndef GUARD_LIBCSC_CSCORDERTYPE_ORDERTYPEFLAGTYPESQLMAPPER_H
#define GUARD_LIBCSC_CSCORDERTYPE_ORDERTYPEFLAGTYPESQLMAPPER_H

#include <cscordertype/ordertypeflagtype/ordertypeflagtypemapperbase.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc
{
	namespace cscordertype
	{
		class OrderTypeFlagTypeSqlMapper : public OrderTypeFlagTypeMapperBase
		{
		public:
			OrderTypeFlagTypeSqlMapper(OrderTypeFlagTypePtr orderTypeFlagType, const basar::db::sql::ResultsetRef resultSet);
			virtual ~OrderTypeFlagTypeSqlMapper();

			static const basar::VarString getSelectSQL(const basar::VarString& orderType);

		protected:
			virtual void doMap();

		private:
			OrderTypeFlagTypeSqlMapper(const OrderTypeFlagTypeSqlMapper &);
			OrderTypeFlagTypeSqlMapper & operator=(const OrderTypeFlagTypeSqlMapper &);

			const basar::db::sql::ResultsetRef m_ResultSet;
		};

	} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_ORDERTYPEFLAGTYPESQLMAPPER_H
