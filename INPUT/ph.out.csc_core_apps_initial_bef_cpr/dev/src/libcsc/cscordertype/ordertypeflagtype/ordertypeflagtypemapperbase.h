#ifndef GUARD_LIBCSC_CSCORDERTYPE_ORDERTYPEFLAGTYPEMAPPERBASE_H
#define GUARD_LIBCSC_CSCORDERTYPE_ORDERTYPEFLAGTYPEMAPPERBASE_H

#include <libbasar_definitions.h>
#include <cscordertype/ordertypeflagtype/ordertypeflagtypeptr.h>

namespace libcsc
{
	namespace cscordertype
	{
		class OrderTypeFlagTypeMapperBase
		{
		public:
			OrderTypeFlagTypeMapperBase(OrderTypeFlagTypePtr orderTypeFlagType);

			void map();

		protected:
			virtual ~OrderTypeFlagTypeMapperBase();

			virtual void doMap() = 0;

			void setOrderType(const basar::VarString& orderType);
			void setName(const basar::VarString& name);
			void setOrderTypeFlagType(const basar::Int16 orderTypeFlagType);
			void setOrderTypeFlag(const basar::Int16 orderTypeFlag);
			void setDescription(const basar::VarString& description);
			void setIndexDKAUA(const basar::Int16 forbidUserChange);

		private:
			OrderTypeFlagTypePtr m_OrderTypeFlagType;
		};

	} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_ORDERTYPEFLAGTYPEMAPPERBASE_H
