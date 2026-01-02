#include "ordertypeflagtype.h"

namespace libcsc
{
	namespace cscordertype
	{
		OrderTypeFlagType::OrderTypeFlagType()
		{
		}

		OrderTypeFlagType::~OrderTypeFlagType()
		{
		}

		const libcsc::VarString & OrderTypeFlagType::getOrderType() const
		{
			return m_OrderType;
		}

		const libcsc::VarString & OrderTypeFlagType::getName() const
		{
			return m_Name;
		}

		OrderTypeFlagTypeEnum OrderTypeFlagType::getOrderTypeFlagType() const
		{
			return m_OrderTypeFlagType;
		}

		const libcsc::Int16 & OrderTypeFlagType::getOrderTypeFlag() const
		{
			return m_OrderTypeFlag;
		}

		const libcsc::VarString & OrderTypeFlagType::getDescription() const
		{
			return m_Description;
		}

		const libcsc::Int16 & OrderTypeFlagType::getIndexDKAUA() const
		{
			return m_IndexDKAUA;
		}

		void OrderTypeFlagType::setOrderType(const basar::VarString& orderType)
		{
			m_OrderType = orderType;
		}

		void OrderTypeFlagType::setName(const basar::VarString& name)
		{
			m_Name = name;
		}

		void OrderTypeFlagType::setOrderTypeFlag(const basar::Int16 orderTypeFlag)
		{
			m_OrderTypeFlag = orderTypeFlag;
		}

		void OrderTypeFlagType::setOrderTypeFlagType(OrderTypeFlagTypeEnum orderTypeFlagType)
		{
			m_OrderTypeFlagType = orderTypeFlagType;
		}

		void OrderTypeFlagType::setDescription(const basar::VarString& description)
		{
			m_Description = description;
		}

		void OrderTypeFlagType::setIndexDKAUA(const basar::Int16 indexDKAUA)
		{
			m_IndexDKAUA = indexDKAUA;
		}


	} // namespace cscordertype
} // namespace libcsc
