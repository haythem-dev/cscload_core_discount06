#ifndef GUARD_LIBCSC_CSCORDERTYPE_ORDERTYPEFLAGTYPE_H
#define GUARD_LIBCSC_CSCORDERTYPE_ORDERTYPEFLAGTYPE_H

#include <cscordertype/ordertypeflagtype/iordertypeflagtype.h>

namespace libcsc
{
	namespace cscordertype
	{
		class OrderTypeFlagType : public IOrderTypeFlagType
		{
			// because of OR mapping
			friend class OrderTypeFlagTypeMapperBase;

		public:
			OrderTypeFlagType();
			virtual ~OrderTypeFlagType();

			virtual const libcsc::VarString&	getOrderType() const;
			virtual const libcsc::VarString&	getName() const;
			virtual OrderTypeFlagTypeEnum		getOrderTypeFlagType() const;
			virtual const libcsc::Int16&		getOrderTypeFlag() const;
			virtual const libcsc::VarString&	getDescription() const;
			virtual const libcsc::Int16&		getIndexDKAUA() const;

			virtual void setOrderType(const basar::VarString& orderType);
			virtual void setName(const basar::VarString& name);
			virtual void setOrderTypeFlagType(const OrderTypeFlagTypeEnum orderTypeFlagType);
			virtual void setOrderTypeFlag(const basar::Int16 orderTypeFlag);
			virtual void setDescription(const basar::VarString& description);
			virtual void setIndexDKAUA(const basar::Int16 indexDKAUA);


		private:
			OrderTypeFlagType(const OrderTypeFlagType &);
			OrderTypeFlagType & operator=(const OrderTypeFlagType &);

			libcsc::VarString		m_OrderType;
			libcsc::VarString		m_Name;
			OrderTypeFlagTypeEnum	m_OrderTypeFlagType;
			libcsc::Int16			m_OrderTypeFlag;
			libcsc::VarString		m_Description;
			libcsc::Int16			m_IndexDKAUA;
		};

	} // namespace cscordertype
} // namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_ORDERTYPEFLAGTYPE_H
