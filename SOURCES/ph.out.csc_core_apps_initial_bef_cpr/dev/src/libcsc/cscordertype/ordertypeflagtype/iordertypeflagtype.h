#ifndef GUARD_LIBCSC_CSCORDERTYPE_IORDERTYPEFLAGTYPE_H
#define GUARD_LIBCSC_CSCORDERTYPE_IORDERTYPEFLAGTYPE_H

#include <libbasar_definitions.h>
#include <datatypes/int16.h>
#include <datatypes/varstring.h>
#include <cscordertype/ordertypeflagtype/ordertypeflagtypeenum.h>

namespace libcsc
{
	namespace cscordertype
	{
		class IOrderTypeFlagType
		{
		public:
			virtual ~IOrderTypeFlagType() {}

			virtual const libcsc::VarString&		getOrderType() const = 0;
			virtual const libcsc::VarString&		getName() const = 0;
			virtual OrderTypeFlagTypeEnum			getOrderTypeFlagType() const = 0;
			virtual const libcsc::Int16&			getOrderTypeFlag() const = 0;
			virtual const libcsc::VarString&		getDescription() const = 0;
			virtual const libcsc::Int16&			getIndexDKAUA() const = 0;

			virtual void setOrderType(const basar::VarString& orderType) = 0;
			virtual void setName(const basar::VarString& name) = 0;
			virtual void setOrderTypeFlagType(const OrderTypeFlagTypeEnum orderTypeFlagType) = 0;
			virtual void setOrderTypeFlag(const basar::Int16 orderTypeFlag) = 0;
			virtual void setDescription(const basar::VarString& description) = 0;
			virtual void setIndexDKAUA(const basar::Int16 indexDKAUA) = 0;
		};

	} // namespace cscordertype
} // namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_IORDERTYPEFLAGTYPE_H
